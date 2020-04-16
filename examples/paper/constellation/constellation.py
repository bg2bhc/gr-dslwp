#%matplotlib inline
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 7})
plt.rcParams.update({'lines.linewidth': 0.75})
plt.rcParams.update({'lines.markersize': 3})
plt.rcParams.update({'font.family': "Helvetica"})

def constellation_diagram(x, station, ax):
    ax.plot(x.real, x.imag, '.', alpha = 0.1)
    ax.set_title(station, fontsize=7, pad=3)
    #ax.axis('equal')
    #ax.set_xlabel('Real Part')
    ax.tick_params(direction='in', length=2, pad=3)
    ax.set_xlim([-4,4])
    ax.set_ylim([-4,4])

def plot_eye(eye, station, ax):
    time = (np.arange(eye.shape[1])-eye.shape[1]//2)/4e3
    ax.plot(time*1e3, eye[:1000,:].T, color = 'C0', alpha = 0.1)
    ax.set_title(station, fontsize=7, pad=3)
    #ax.ylabel('Amplitude')
    #ax.set_xlabel('Time (ms)')
    ax.tick_params(direction='in', length=2, pad=3)
    ax.set_xlim([-4,4])
    ax.set_ylim([-4,4])
    #ax.savefig('eye.png', dpi = 300, bbox_inches = 'tight')

dwingeloo1 = np.fromfile('constell1_Dwingeloo.c64', dtype = 'complex64')
dwingeloo2 = np.fromfile('constell2_Dwingeloo.c64', dtype = 'complex64')
dwingeloo = np.concatenate((dwingeloo1,dwingeloo2), axis=0)

wakayama1 = np.fromfile('constell1_Wakayama.c64', dtype = 'complex64')
wakayama2 = np.fromfile('constell2_Wakayama.c64', dtype = 'complex64')
wakayama = np.concatenate((wakayama1,wakayama2), axis=0)

shahe1 = np.fromfile('constell1_Shahe.c64', dtype = 'complex64')
shahe2 = np.fromfile('constell2_Shahe.c64', dtype = 'complex64')
shahe = np.concatenate((shahe1,shahe2), axis=0)

harbin1 = np.fromfile('constell1_Harbin.c64', dtype = 'complex64')
harbin2 = np.fromfile('constell2_Harbin.c64', dtype = 'complex64')
harbin = np.concatenate((harbin1,harbin2), axis=0)

#fig, ax = plt.subplots(nrows = 2, ncols = 4, figsize = (20,10), facecolor = 'w')
fig, ax = plt.subplots(nrows = 2, ncols = 4, facecolor = 'w', sharey=True)
fig.set_figwidth(215/25.4)
fig.set_figheight(215/25.4/2)
#fig.set_figheight(20)

constellation_diagram(dwingeloo, 'Dwingeloo', ax[0][0])
constellation_diagram(wakayama, 'Wakayama', ax[0][1])
constellation_diagram(shahe, 'Shahe', ax[0][2])
constellation_diagram(harbin, 'Harbin', ax[0][3])

eye1 = np.fromfile('eye1_dwingeloo.c64', dtype = 'complex64')
eye2 = np.fromfile('eye2_dwingeloo.c64', dtype = 'complex64')
eyes = (eye1, eye2)
eye = np.concatenate(eyes).reshape((-1,32))
eye = np.vstack((eye[0:(eye.shape[0]-2),:].T, eye[1:(eye.shape[0]-1):,0])).T
eye_I = eye.real;
eye_Q = eye.imag;
plot_eye(np.concatenate((eye_I, eye_Q)), 'Dwingeloo', ax[1][0])

eye1 = np.fromfile('eye1_wakayama.c64', dtype = 'complex64')
eye2 = np.fromfile('eye2_wakayama.c64', dtype = 'complex64')
eyes = (eye1, eye2)
eye = np.concatenate(eyes).reshape((-1,32))
eye = np.vstack((eye[0:(eye.shape[0]-2),:].T, eye[1:(eye.shape[0]-1):,0])).T
eye_I = eye.real;
eye_Q = eye.imag;
plot_eye(np.concatenate((eye_I, eye_Q)), 'Wakayama', ax[1][1])

eye1 = np.fromfile('eye1_shahe.c64', dtype = 'complex64')
eye2 = np.fromfile('eye2_shahe.c64', dtype = 'complex64')
eyes = (eye1, eye2)
eye = np.concatenate(eyes).reshape((-1,32))
eye = np.vstack((eye[0:(eye.shape[0]-2),:].T, eye[1:(eye.shape[0]-1):,0])).T
eye_I = eye.real;
eye_Q = eye.imag;
plot_eye(np.concatenate((eye_I, eye_Q)), 'Shahe', ax[1][2])

eye1 = np.fromfile('eye1_harbin.c64', dtype = 'complex64')
eye2 = np.fromfile('eye2_harbin.c64', dtype = 'complex64')
eyes = (eye1, eye2)
eye = np.concatenate(eyes).reshape((-1,32))
eye = np.vstack((eye[0:(eye.shape[0]-2),:].T, eye[1:(eye.shape[0]-1):,0])).T
eye_I = eye.real;
eye_Q = eye.imag;
plot_eye(np.concatenate((eye_I, eye_Q)), 'Harbin', ax[1][3])

ax[0][0].set_ylabel('Image part', labelpad=1)
ax[1][0].set_ylabel('Amplitude', labelpad=1)

#plt.savefig('constellation.png', dpi = 300)
plt.savefig('constellation.png', dpi = 300, bbox_inches = 'tight')
