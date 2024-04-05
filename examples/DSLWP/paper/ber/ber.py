#%matplotlib inline
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import chi2
from scipy.stats import ncx2
from scipy.special import erfc
from scipy import integrate
np.seterr(divide='ignore');

plt.rcParams.update({'font.size': 7})
plt.rcParams.update({'lines.linewidth': 0.75})
plt.rcParams.update({'lines.markersize': 3})
plt.rcParams.update({'font.family': "Helvetica"})

N_fft = 256
fs = 2000
Rb = 250/32

def lrtc_ber_formula(ebn0_dB, n_bin):
    ebn0 = 10**(0.1*ebn0_dB)
    cnr = ebn0 * Rb / fs * N_fft;
    ber = np.zeros(len(cnr))
 
    for i in range(len(cnr)):
        y = lambda x: ncx2.pdf(x, 2, cnr[i]*2) * (chi2.cdf(x, 2)**(n_bin-1))
        p, err = integrate.quad(y, np.NINF, np.PINF)    
        ber[i] =(1-p)*(n_bin/2)/(n_bin-1)
    return ber

#plt.figure(figsize = (95/25.4, 95/25.4*0.7), facecolor = 'w', edgecolor=(0.89803921568627450, 0.89803921568627450, 0.89803921568627450))
fig=plt.figure(figsize = (95/25.4, 95/25.4*0.7), facecolor = 'w')
#fig.patch.set_facecolor('xkcd:mint green')
ebn0s_formula = np.linspace(5, 18, 30)

plt.plot(ebn0s_formula, np.log10(0.5 * erfc(np.sqrt(10**(0.1*ebn0s_formula)))), label='BPSK coherent', linestyle = '-.', color='C6')
plt.plot(ebn0s_formula, np.log10(0.5 * erfc(np.sqrt(0.5*10**(0.1*ebn0s_formula)))), label='FPSK coherent', linestyle = '-.', color='C3')
plt.plot(ebn0s_formula, np.log10(0.5 * np.exp(-0.5*10**(0.1*ebn0s_formula))), label='FSK non-coherent, theoretical limit', linestyle = '--', color='C0')
plt.plot(ebn0s_formula, np.log10(lrtc_ber_formula(ebn0s_formula, 4)), label='LRTC, $N_{bin}=4$', color='C1')
plt.plot(ebn0s_formula, np.log10(0.5 * np.exp(-0.5/2*10**(0.1*ebn0s_formula))), label='FSK non-coherent, 2× bandwidth', linestyle = '--', color='C1')
plt.plot(ebn0s_formula, np.log10(lrtc_ber_formula(ebn0s_formula, 16)), label='LRTC, $N_{bin}=16$', color='C2')
plt.plot(ebn0s_formula, np.log10(0.5 * np.exp(-0.5/8*10**(0.1*ebn0s_formula))), label='FSK non-coherent, 8× bandwidth', linestyle = '--', color='C2')
plt.plot(ebn0s_formula, np.log10(lrtc_ber_formula(ebn0s_formula, 64)), label='LRTC, $N_{bin}=64$', color='C4')
plt.plot(ebn0s_formula, np.log10(lrtc_ber_formula(ebn0s_formula, 256)), label='LRTC, $N_{bin}=256$', color='C9')

plt.legend(fontsize=5)
plt.xlabel('$E_{b}/N_{0}$ (dB)', labelpad=1)
plt.ylabel('$log_{10}(BER)$', labelpad=0)
plt.ylim([-10, 0]);
plt.xlim([5, 18]);
plt.tick_params(direction='in', length=2, pad=2, top=True, right=True)

plt.savefig('ber.png', dpi = 300, bbox_inches = 'tight');
