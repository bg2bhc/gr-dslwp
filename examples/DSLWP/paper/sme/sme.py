import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import matplotlib.dates as mdates
from astropy.time import Time, TimeDelta
import astropy.constants

plt.rcParams.update({'font.size': 7})
plt.rcParams.update({'lines.linewidth': 0.75})
plt.rcParams.update({'font.family': "Helvetica"})
figsize = [100/25.4, 100/25.4*0.7]

c = astropy.constants.c.value

mjd_unixtimestamp_offset = 10587.5
seconds_in_day = 3600 * 24

def mjd2unixtimestamp(m):
    return (m - mjd_unixtimestamp_offset) * seconds_in_day

def load_file(path):
    ncols = 25
    data = np.fromfile(path, sep=' ')
    return data.reshape((data.size // ncols, ncols))

def load_data(path, start, end):
    data = load_file(path)
    t = Time(mjd2unixtimestamp(data[:,0]), format='unix')
    sel = (Time(start) <= t) & (t <= Time(end))
    t = t[sel]
    data = data[sel,:]
    
    return t, data

t, data = load_data('SME.txt', '2018-10-07T09:50:00', '2018-10-07T12:10:00')
t2, data2 = load_data('SME2.txt', '2018-10-19T16:50:00', '2018-10-19T18:50:00')

def rangerate(x):
    return np.sum(x[:,:3] * x[:,3:], axis=1) / np.sqrt(np.sum(x[:,:3]**2, axis=1)) * 1e3

def rangerate2doppler(x, freq = 436.4e6):
    return -x * freq / c

direct_doppler = rangerate2doppler(rangerate(data[:,1:7]))
direct_doppler_435 = rangerate2doppler(rangerate(data[:,1:7]), freq = 435.4e6)
direct_t = t

def compute_moonbounce(data):
    long, lat = np.meshgrid(np.linspace(-np.pi, np.pi, 1000), np.linspace(-np.pi/2, np.pi/2, 1000))
    moon_radius = 1737
    moon_x = moon_radius * np.cos(long) * np.cos(lat)
    moon_y = moon_radius * np.sin(long) * np.cos(lat)
    moon_z = moon_radius * np.sin(lat)
    min_dist = np.empty(data.shape[0])
    reflection_point_long = np.empty(data.shape[0])
    reflection_point_lat = np.empty(data.shape[0])
    for j in range(data.shape[0]):
        dist = np.sqrt((data[j,19]-moon_x)**2 + (data[j,20]-moon_y)**2 + (data[j,21]-moon_z)**2) + np.sqrt((data[j,13]-moon_x)**2 + (data[j,14]-moon_y)**2 + (data[j,15]-moon_z)**2) 
        min_dist[j] = np.min(dist)
        minpoint = np.unravel_index(np.argmin(dist), dist.shape)
        reflection_point_long[j] = long[minpoint]
        reflection_point_lat[j] = lat[minpoint]
    return min_dist, reflection_point_long, reflection_point_lat

min_dist, reflection_point_long, reflection_point_lat = compute_moonbounce(data)
min_dist_2, reflection_point_long_2, reflection_point_lat_2 = compute_moonbounce(data2)

moonbounce_rangerate = np.diff(min_dist)/np.diff(mjd2unixtimestamp(data[:,0])) * 1e3
moonbounce_doppler = rangerate2doppler(moonbounce_rangerate)
moonbounce_doppler_435 = rangerate2doppler(moonbounce_rangerate, 435.4e6)
moonbounce_t = Time(mjd2unixtimestamp((data[:-1,0] + data[1:,0])/2), format='unix')

def waterfall_plot(image_path, start_time, timespan, doppler_offset = 750, band435 = False):
    img = mpimg.imread(image_path)
    img_start = Time(start_time)
    img_end = img_start + TimeDelta(timespan, format='sec')
    plt.figure(figsize=figsize, facecolor='w')
    plt.plot(direct_t.datetime, direct_doppler if not band435 else direct_doppler_435)
    plt.plot(moonbounce_t.datetime, moonbounce_doppler if not band435 else moonbounce_doppler_435)
    if band435:
        for offset in 1000 + 312.5*np.arange(4):
            plt.plot(direct_t.datetime, direct_doppler + offset, color='C0', linewidth=1, linestyle=':')
            plt.plot(moonbounce_t.datetime, moonbounce_doppler + offset, color='C1', linewidth=1, linestyle=':')
    freq = '436.4MHz' if not band435 else '435.4MHz'
    #plt.title(f'DSLWP-B Doppler at {freq} and signal recorded in Dwingeloo (offset {-doppler_offset}Hz)')
    plt.xlabel('UTC Time', labelpad=1)
    plt.ylabel('Doppler (Hz)', labelpad=1)
    plt.legend(['Prediction, direct path', 'Prediction, moonbounce path'], fontsize=5)

    min_freq = -1000 if not band435 else 900-1800
    max_freq = 1000 if not band435 else 900+1800
    plt.imshow(img, extent = (mdates.date2num(img_start.datetime), mdates.date2num(img_end.datetime), min_freq-doppler_offset, max_freq-doppler_offset),\
               aspect = 'auto');

waterfall_plot('dslwp_sme1.png', '2018-10-07T10:37:18', 3203.4544)
plt.savefig('sme.png', dpi=300)
