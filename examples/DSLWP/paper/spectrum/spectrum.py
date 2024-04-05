import numpy as np
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 7})
plt.rcParams.update({'lines.linewidth': 0.75})
plt.rcParams.update({'font.family': "Helvetica"})

figsize = [95/25.4, 95/25.4*0.6]

def spectrum(path, skip):
    with open(path, 'rb') as f:
        f.seek((skip + 10 * 40000) * 8)
        x = np.fromfile(f, dtype = 'complex64', count = 400000)
    N = 4096
    return np.fft.fftshift(np.average(np.abs(np.fft.fft(x[:x.size//N*N].reshape((-1,N))))**2, axis = 0))

dwingeloo = spectrum('c64_B_436_Dwingeloo_2019-07-05.raw', 38440000)
wakayama = spectrum('c64_B_436_Wakayama_2019-07-05.raw', 91894696)
shahe = spectrum('c64_B_436_Shahe_1562311500_1562319300.raw', 36977196)
harbin = spectrum('c64_B_436_Harbin_1562311740_1562319060.raw', 27377251)

N = 4096
dwingeloo /= np.average(dwingeloo[1000:1500])
wakayama /= np.average(wakayama[1000:1500])
shahe /= np.average(shahe[1000:1500])
harbin /= np.average(harbin[1000:1500])
sel = slice(1750,2000)

plt.figure(figsize=figsize, facecolor = 'w')
freq = np.fft.fftshift(np.fft.fftfreq(N, 1/40e3))[sel]
plt.plot(freq, 10*np.log10(dwingeloo[sel]))
plt.plot(freq, 10*np.log10(wakayama[sel]))
plt.plot(freq, 10*np.log10(shahe[sel]))
plt.plot(freq, 10*np.log10(harbin[sel]))
plt.legend(['Dwingeloo', 'Wakayama', 'Shahe', 'Harbin'], fontsize=5)
plt.xlabel('Frequency (Hz)', labelpad=1)
plt.ylabel('PSD (dB)', labelpad=1)
plt.tick_params(direction='in', length=2, pad=2)
#plt.title('Spectrum')
plt.xlim([-3000,-400])
plt.ylim([-2,20])
plt.savefig('spectrum.png', dpi = 300, bbox_inches = 'tight', top=True, right=True);
