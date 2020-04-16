#%matplotlib inline
import numpy as np
import matplotlib.pyplot as plt
import scipy.optimize

plt.rcParams.update({'font.size': 7})
plt.rcParams.update({'lines.linewidth': 0.75})
plt.rcParams.update({'lines.markersize': 3})
plt.rcParams.update({'font.family': "Helvetica"})
figsize = [140/25.4, 140/25.4*0.7]

import pathlib
import functools
import vlbi

c = 299792458 # speed of light in m/s
fs = 40000


observation = np.dtype([('utc', np.float32), ('delta_range', np.float32), ('delta_velocity', np.float32), ('freq', np.float32), ('max_corr', np.float32)])

def compute_observation(data):
    time = data['time'][0] + 0.5*data['corr'].size/fs
    corr_peak = np.argmax(np.abs(data['corr']))
    corr_peak += vlbi.peak_estimator_parabola(np.abs(data['corr'][corr_peak-1:corr_peak+2]))
    delta_range = vlbi.delta_range(corr_peak, data['corr'].size, data['time'][0] - data['time'][1])
    delta_velocity =  -(data['freq_bin']*fs/data['corr'].size + data['f_lo'][0,0] - data['f_lo'][1,0]) * c / data['freq']
    return time, delta_range, delta_velocity, data['freq'], np.max(np.abs(data['corr']))


path = pathlib.Path('data_out')

observations = np.fromiter((compute_observation(np.load(str(p))) for p in path.iterdir()), dtype=observation)
# filter by delta_range
observations = observations[np.abs(observations['delta_range']) < 10e6]

def range_doppler(tracking):
    return np.sqrt(np.sum(tracking[:,0:3]**2, axis=1))*1e3

trk = vlbi.load_doppler_file('VLBI_Doppler.txt')
delta_range = range_doppler(trk[:,1:]) - range_doppler(trk[:,7:])
delta_velocity = vlbi.range_rate(trk[:,1:]) - vlbi.range_rate(trk[:,7:])
utc = vlbi.mjd2unixtimestamp(trk[:,0])

trk = vlbi.load_doppler_file('VLBI_Doppler_old.txt')
delta_range_old = range_doppler(trk[:,1:]) - range_doppler(trk[:,7:])
delta_velocity_old = vlbi.range_rate(trk[:,1:]) - vlbi.range_rate(trk[:,7:])

trk = vlbi.load_doppler_file('VLBI_tracking_20180610.txt')
delta_range_track = range_doppler(trk[:,1:]) - range_doppler(trk[:,7:])
delta_velocity_track = vlbi.range_rate(trk[:,1:]) - vlbi.range_rate(trk[:,7:])

obs_435 = observations[observations['freq'] == 435.4e6]
obs_436 = observations[observations['freq'] == 436.4e6]

start = np.min(observations['utc']) - 120
end = np.max(observations['utc']) + 120
trk_sel = (utc >= start) & (utc <= end)

p = np.poly1d(np.polyfit(np.concatenate((obs_435['utc']-obs_435['utc'][0], obs_436['utc']-obs_435['utc'][0])), np.concatenate((obs_435['delta_velocity'], obs_436['delta_velocity'])), 2))

plt.figure(figsize=figsize, facecolor='w')
plt.plot(utc[trk_sel], delta_velocity_old[trk_sel])
plt.plot(utc[trk_sel], delta_velocity[trk_sel])
plt.plot(utc[trk_sel], delta_velocity_track[trk_sel])
plt.plot(utc[trk_sel], p(utc[trk_sel] - obs_435['utc'][0]), '--')
plt.plot(np.concatenate((obs_435['utc'], obs_436['utc'])), np.concatenate((obs_435['delta_velocity'], obs_436['delta_velocity'])), 'x')
plt.title('Delta-velocity')
plt.xlabel('UNIX timestamp (s)')
plt.ylabel('Delta-velocity (m/s)')
plt.legend(['Old elements', 'New elements', '20180610 tracking file', 'Degree 2 polynomial fit', 'VLBI observations'])
plt.savefig('fig1.png', dpi = 300, bbox_inches = 'tight')

plt.figure(figsize=figsize, facecolor='w')
plt.plot(utc[trk_sel], delta_velocity_old[trk_sel] - p(utc[trk_sel] - obs_435['utc'][0]))
plt.plot(utc[trk_sel], delta_velocity[trk_sel] - p(utc[trk_sel] - obs_435['utc'][0]))
plt.plot(utc[trk_sel], delta_velocity_track[trk_sel] - p(utc[trk_sel] - obs_435['utc'][0]))
plt.plot(np.concatenate((obs_435['utc'], obs_436['utc'])), np.concatenate((obs_435['delta_velocity'] - p(obs_435['utc'] - obs_435['utc'][0]), obs_436['delta_velocity'] - p(obs_436['utc'] - obs_435['utc'][0]))), 'x')
plt.title('Delta-velocity difference with polynomial fit')
plt.xlabel('UNIX timestamp (s)')
plt.ylabel('Delta-velocity (m/s)')
plt.legend(['Old elements', 'New elements', '20180610 tracking file', 'VLBI observations'])
plt.savefig('fig2.png', dpi = 300, bbox_inches = 'tight')


plt.figure(figsize=figsize, facecolor='w')
plt.plot(np.concatenate((obs_435['utc'], obs_436['utc'])), np.concatenate((obs_435['delta_velocity'] - np.interp(obs_435['utc'], utc, delta_velocity), obs_436['delta_velocity'] - np.interp(obs_436['utc'], utc, delta_velocity_old))), 'x')
plt.plot(np.concatenate((obs_435['utc'], obs_436['utc'])), np.concatenate((obs_435['delta_velocity'] - np.interp(obs_435['utc'], utc, delta_velocity), obs_436['delta_velocity'] - np.interp(obs_436['utc'], utc, delta_velocity))), 'x')
plt.plot(np.concatenate((obs_435['utc'], obs_436['utc'])), np.concatenate((obs_435['delta_velocity'] - np.interp(obs_435['utc'], utc, delta_velocity), obs_436['delta_velocity'] - np.interp(obs_436['utc'], utc, delta_velocity_track))), 'x')
plt.plot(np.concatenate((obs_435['utc'], obs_436['utc'])), np.concatenate((obs_435['delta_velocity'] - p(obs_435['utc'] - obs_435['utc'][0]), obs_436['delta_velocity'] - p(obs_436['utc'] - obs_435['utc'][0]))), 'x')
plt.title('Delta-velocity residuals')
plt.xlabel('UNIX timestamp (s)')
plt.ylabel('Residual (m/s)')
plt.legend(['Old elements', 'New elements', '20180610 tracking file', 'Degree 2 polynomial fit']);
plt.savefig('fig3.png', dpi = 300, bbox_inches = 'tight')

print('RMS errors')
print(np.sqrt(np.average(np.square(np.concatenate((obs_435['delta_velocity'] - np.interp(obs_435['utc'], utc, delta_velocity), obs_436['delta_velocity'] - np.interp(obs_436['utc'], utc, delta_velocity_old)))))))
print(np.sqrt(np.average(np.square(np.concatenate((obs_435['delta_velocity'] - np.interp(obs_435['utc'], utc, delta_velocity), obs_436['delta_velocity'] - np.interp(obs_436['utc'], utc, delta_velocity)))))))
print(np.sqrt(np.average(np.square(np.concatenate((obs_435['delta_velocity'] - np.interp(obs_435['utc'], utc, delta_velocity), obs_436['delta_velocity'] - np.interp(obs_436['utc'], utc, delta_velocity_track)))))))
print(np.sqrt(np.average(np.square(np.concatenate((obs_435['delta_velocity'] - p(obs_435['utc'] - obs_435['utc'][0]), obs_436['delta_velocity'] - p(obs_436['utc'] - obs_435['utc'][0])))))))

fig, ax = plt.subplots(nrows = 2, ncols = 2, figsize=figsize, facecolor = 'w')
#plt.figure(figsize=figsize, facecolor='w')
ax[0][0].plot(utc[trk_sel], delta_range[trk_sel]/1000)
ax[0][0].plot(obs_435['utc'], obs_435['delta_range']/1000, 'x')
ax[0][0].plot(obs_436['utc'], obs_436['delta_range']/1000, 'x')
#ax[0][0].set_title('Delta-range')
ax[0][0].set_xlabel('UNIX timestamp (s)', labelpad=1)
ax[0][0].set_ylabel('Delta-range (km)', labelpad=-2)
ax[0][0].tick_params(direction='in', length=2, pad=3, top=True, right=True)
ax[0][0].set_ylim([-1500, 1200])
ax[0][0].legend(['Prediction', '435.4MHz VLBI', '436.4MHz VLBI'], fontsize=5)

ax[0][1].plot(utc[trk_sel], delta_velocity[trk_sel])
ax[0][1].plot(obs_435['utc'], obs_435['delta_velocity'], 'x')
ax[0][1].plot(obs_436['utc'], obs_436['delta_velocity'], 'x')
#ax[0][1].set_title('Delta-velocity')
ax[0][1].set_xlabel('UNIX timestamp (s)', labelpad=1)
ax[0][1].set_ylabel('Delta-velocity (m/s)', labelpad=1)
ax[0][1].tick_params(direction='in', length=2, pad=3, top=True, right=True)
ax[0][1].legend(['Prediction', '435.4MHz VLBI', '436.4MHz VLBI'], fontsize=5)

dr_435=[obs_435['utc'], obs_435['delta_range'] - np.interp(obs_435['utc'], utc, delta_range_track)]
idex=np.argsort(dr_435[0][:])
ax[1][0].plot(dr_435[0][idex], dr_435[1][idex]/1000, 'x-')
print('RMS errors DR 435')
print(np.sqrt(np.average(np.square(dr_435[1][:]))))

dr_436=[obs_436['utc'], obs_436['delta_range'] - np.interp(obs_436['utc'], utc, delta_range_track)]
idex=np.argsort(dr_436[0][:])
ax[1][0].plot(dr_436[0][idex], dr_436[1][idex]/1000, 'x-')
print('RMS errors DR 436')
print(np.sqrt(np.average(np.square(dr_436[1][:]))))

#ax[1][0].set_title('Delta-range residuals')
ax[1][0].set_xlabel('UNIX timestamp (s)', labelpad=1)
ax[1][0].set_ylabel('Delta-range residual (km)', labelpad=1)
ax[1][0].tick_params(direction='in', length=2, pad=3, top=True, right=True)
ax[1][0].set_ylim([-67, 67])
ax[1][0].legend(['435.4MHz VLBI', '436.4MHz VLBI'], fontsize=5)

dv_435=[obs_435['utc'], obs_435['delta_velocity'] - np.interp(obs_435['utc'], utc, delta_velocity_track)]
idex=np.argsort(dv_435[0][:])
ax[1][1].plot(dv_435[0][idex], dv_435[1][idex], 'x-')
print('RMS errors DV 435')
print(np.sqrt(np.average(np.square(dv_435[1][:]))))

dv_436=[obs_436['utc'], obs_436['delta_velocity'] - np.interp(obs_436['utc'], utc, delta_velocity_track)]
idex=np.argsort(dv_436[0][:])
ax[1][1].plot(dv_436[0][idex], dv_436[1][idex], 'x-')
print('RMS errors DV 436')
print(np.sqrt(np.average(np.square(dv_436[1][:]))))

#ax[1][1].set_title('Delta-velocity residuals')
ax[1][1].set_xlabel('UNIX timestamp (s)', labelpad=1)
ax[1][1].set_ylabel('Delta-velocity residual (m/s)', labelpad=1)
ax[1][1].tick_params(direction='in', length=2, pad=3, top=True, right=True)
ax[1][1].set_ylim([-0.25, 0.3])
ax[1][1].legend(['435.4MHz VLBI', '436.4MHz VLBI'], fontsize=5);

fig.savefig('fig4.png', dpi = 300, bbox_inches = 'tight')

plt.figure(figsize=figsize, facecolor='w')
plt.plot(obs_435['utc'], obs_435['max_corr'], 'x')
plt.plot(obs_436['utc'], obs_436['max_corr'], 'x')
plt.title('Correlation magnitude')
plt.xlabel('UNIX timestamp (s)')
plt.ylabel('Magnitude (linear)')
plt.legend(['435.4MHz VLBI', '436.4MHz VLBI']);
plt.savefig('fig8.png', dpi = 300, bbox_inches = 'tight')
