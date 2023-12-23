/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <gnuradio/expj.h>
#include "lrtc_mod_bc_impl.h"

namespace gr {
  namespace dslwp {

    lrtc_mod_bc::sptr
    lrtc_mod_bc::make()
    {
      return gnuradio::get_initial_sptr
        (new lrtc_mod_bc_impl());
    }

    /*
     * The private constructor
     */
    lrtc_mod_bc_impl::lrtc_mod_bc_impl()
      : gr::sync_interpolator("lrtc_mod_bc",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), 256)
    {
      d_pacc = 0.0f;
      d_dp = 101.0f/256.0f*M_PI; //d_dp = 1.2394; f_dev = d_dp/2/pi*2000Hz = 394.53 Hz
    }

    /*
     * Our virtual destructor.
     */
    lrtc_mod_bc_impl::~lrtc_mod_bc_impl()
    {
    }

    int
    lrtc_mod_bc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int i, j;

      static gr_complex asm32[] = 
      {
	gr_complex(0.986752, -0.162236), gr_complex(0.961165, -0.275976), gr_complex(0.909253, -0.416245), gr_complex(0.82381, -0.566866),
	gr_complex(0.704089, -0.710112), gr_complex(0.554654, -0.832081), gr_complex(0.382467, -0.923969), gr_complex(0.19505, -0.980793),
	gr_complex(-6e-06, -1.0), gr_complex(-0.195091, -0.980785), gr_complex(-0.382683, -0.92388), gr_complex(-0.55557, -0.83147),
	gr_complex(-0.707107, -0.707107), gr_complex(-0.83147, -0.55557), gr_complex(-0.923879, -0.382684), gr_complex(-0.980785, -0.195092),
	gr_complex(-1.0, -1.2e-05), gr_complex(-0.980801, 0.19501), gr_complex(-0.924059, 0.38225), gr_complex(-0.832692, 0.553737),
	gr_complex(-0.713104, 0.701059), gr_complex(-0.578055, 0.815998), gr_complex(-0.449249, 0.893407), gr_complex(-0.35495, 0.934885),
	gr_complex(-0.320174, 0.947359), gr_complex(-0.35495, 0.934885), gr_complex(-0.449249, 0.893407), gr_complex(-0.578055, 0.815998),
	gr_complex(-0.713104, 0.701059), gr_complex(-0.832692, 0.553737), gr_complex(-0.924059, 0.38225), gr_complex(-0.980801, 0.195012),
	gr_complex(-1.0, 0.0), gr_complex(-0.980801, -0.195012), gr_complex(-0.924059, -0.38225), gr_complex(-0.832692, -0.553737),
	gr_complex(-0.713104, -0.701059), gr_complex(-0.578055, -0.815998), gr_complex(-0.449249, -0.893407), gr_complex(-0.354949, -0.934886),
	gr_complex(-0.320163, -0.947363), gr_complex(-0.354874, -0.934914), gr_complex(-0.44883, -0.893617), gr_complex(-0.576256, -0.817269),
	gr_complex(-0.707107, -0.707107), gr_complex(-0.817269, -0.576256), gr_complex(-0.893617, -0.44883), gr_complex(-0.934915, -0.354872),
	gr_complex(-0.947366, -0.320152), gr_complex(-0.934915, -0.354872), gr_complex(-0.893617, -0.44883), gr_complex(-0.817269, -0.576256),
	gr_complex(-0.707107, -0.707107), gr_complex(-0.576256, -0.817269), gr_complex(-0.44883, -0.893617), gr_complex(-0.354872, -0.934915),
	gr_complex(-0.320152, -0.947366), gr_complex(-0.354872, -0.934915), gr_complex(-0.44883, -0.893617), gr_complex(-0.576256, -0.817269),
	gr_complex(-0.707107, -0.707107), gr_complex(-0.817269, -0.576256), gr_complex(-0.893617, -0.44883), gr_complex(-0.934914, -0.354874),
	gr_complex(-0.947363, -0.320163), gr_complex(-0.934886, -0.354949), gr_complex(-0.893407, -0.449249), gr_complex(-0.815998, -0.578055),
	gr_complex(-0.701059, -0.713104), gr_complex(-0.553737, -0.832692), gr_complex(-0.38225, -0.924059), gr_complex(-0.195012, -0.980801),
	gr_complex(-0.0, -1.0), gr_complex(0.195012, -0.980801), gr_complex(0.38225, -0.924059), gr_complex(0.553737, -0.832692),
	gr_complex(0.701059, -0.713104), gr_complex(0.815998, -0.578055), gr_complex(0.893407, -0.449249), gr_complex(0.934885, -0.35495),
	gr_complex(0.947359, -0.320174), gr_complex(0.934885, -0.35495), gr_complex(0.893407, -0.449249), gr_complex(0.815998, -0.578055),
	gr_complex(0.701059, -0.713104), gr_complex(0.553737, -0.832692), gr_complex(0.38225, -0.924059), gr_complex(0.195012, -0.980801),
	gr_complex(-0.0, -1.0), gr_complex(-0.195012, -0.980801), gr_complex(-0.38225, -0.924059), gr_complex(-0.553737, -0.832692),
	gr_complex(-0.701059, -0.713104), gr_complex(-0.815998, -0.578055), gr_complex(-0.893407, -0.449249), gr_complex(-0.934885, -0.35495),
	gr_complex(-0.947359, -0.320174), gr_complex(-0.934885, -0.35495), gr_complex(-0.893407, -0.449249), gr_complex(-0.815998, -0.578055),
	gr_complex(-0.701059, -0.713104), gr_complex(-0.553737, -0.832692), gr_complex(-0.38225, -0.924059), gr_complex(-0.19501, -0.980801),
	gr_complex(1.2e-05, -1.0), gr_complex(0.195092, -0.980785), gr_complex(0.382684, -0.923879), gr_complex(0.55557, -0.83147),
	gr_complex(0.707107, -0.707107), gr_complex(0.83147, -0.55557), gr_complex(0.92388, -0.382683), gr_complex(0.980785, -0.19509),
	gr_complex(1.0, 0.0), gr_complex(0.980785, 0.19509), gr_complex(0.92388, 0.382683), gr_complex(0.83147, 0.55557),
	gr_complex(0.707107, 0.707107), gr_complex(0.55557, 0.83147), gr_complex(0.382683, 0.92388), gr_complex(0.19509, 0.980785),
	gr_complex(0.0, 1.0), gr_complex(-0.19509, 0.980785), gr_complex(-0.382683, 0.92388), gr_complex(-0.55557, 0.83147),
	gr_complex(-0.707107, 0.707107), gr_complex(-0.83147, 0.55557), gr_complex(-0.92388, 0.382683), gr_complex(-0.980785, 0.19509),
	gr_complex(-1.0, 0.0), gr_complex(-0.980785, -0.19509), gr_complex(-0.92388, -0.382683), gr_complex(-0.83147, -0.55557),
	gr_complex(-0.707107, -0.707107), gr_complex(-0.55557, -0.83147), gr_complex(-0.382683, -0.92388), gr_complex(-0.19509, -0.980785),
	gr_complex(-0.0, -1.0), gr_complex(0.19509, -0.980785), gr_complex(0.382683, -0.92388), gr_complex(0.55557, -0.83147),
	gr_complex(0.707107, -0.707107), gr_complex(0.83147, -0.55557), gr_complex(0.92388, -0.382683), gr_complex(0.980785, -0.19509),
	gr_complex(1.0, 0.0), gr_complex(0.980785, 0.19509), gr_complex(0.92388, 0.382683), gr_complex(0.83147, 0.55557),
	gr_complex(0.707107, 0.707107), gr_complex(0.55557, 0.83147), gr_complex(0.382683, 0.92388), gr_complex(0.19509, 0.980785),
	gr_complex(0.0, 1.0), gr_complex(-0.19509, 0.980785), gr_complex(-0.382683, 0.92388), gr_complex(-0.55557, 0.83147),
	gr_complex(-0.707107, 0.707107), gr_complex(-0.83147, 0.55557), gr_complex(-0.92388, 0.382683), gr_complex(-0.980785, 0.19509),
	gr_complex(-1.0, 0.0), gr_complex(-0.980785, -0.19509), gr_complex(-0.92388, -0.382683), gr_complex(-0.83147, -0.55557),
	gr_complex(-0.707107, -0.707107), gr_complex(-0.55557, -0.83147), gr_complex(-0.382684, -0.923879), gr_complex(-0.195092, -0.980785),
	gr_complex(-1.2e-05, -1.0), gr_complex(0.19501, -0.980801), gr_complex(0.38225, -0.924059), gr_complex(0.553737, -0.832692),
	gr_complex(0.701059, -0.713104), gr_complex(0.815998, -0.578055), gr_complex(0.893407, -0.449249), gr_complex(0.934885, -0.35495),
	gr_complex(0.947359, -0.320174), gr_complex(0.934885, -0.35495), gr_complex(0.893407, -0.449249), gr_complex(0.815998, -0.578055),
	gr_complex(0.701059, -0.713104), gr_complex(0.553737, -0.832692), gr_complex(0.38225, -0.924059), gr_complex(0.19501, -0.980801),
	gr_complex(-1.2e-05, -1.0), gr_complex(-0.195092, -0.980785), gr_complex(-0.382684, -0.923879), gr_complex(-0.55557, -0.83147),
	gr_complex(-0.707107, -0.707107), gr_complex(-0.83147, -0.55557), gr_complex(-0.92388, -0.382683), gr_complex(-0.980785, -0.19509),
	gr_complex(-1.0, 0.0), gr_complex(-0.980785, 0.19509), gr_complex(-0.92388, 0.382683), gr_complex(-0.83147, 0.55557),
	gr_complex(-0.707107, 0.707107), gr_complex(-0.55557, 0.83147), gr_complex(-0.382683, 0.92388), gr_complex(-0.19509, 0.980785),
	gr_complex(0.0, 1.0), gr_complex(0.19509, 0.980785), gr_complex(0.382683, 0.92388), gr_complex(0.55557, 0.83147),
	gr_complex(0.707107, 0.707107), gr_complex(0.83147, 0.55557), gr_complex(0.923879, 0.382684), gr_complex(0.980785, 0.195092),
	gr_complex(1.0, 1.2e-05), gr_complex(0.980801, -0.19501), gr_complex(0.924059, -0.38225), gr_complex(0.832692, -0.553737),
	gr_complex(0.713104, -0.701059), gr_complex(0.578055, -0.815998), gr_complex(0.449249, -0.893407), gr_complex(0.35495, -0.934885),
	gr_complex(0.320174, -0.947359), gr_complex(0.35495, -0.934885), gr_complex(0.449249, -0.893407), gr_complex(0.578055, -0.815998),
	gr_complex(0.713104, -0.701059), gr_complex(0.832692, -0.553737), gr_complex(0.924059, -0.38225), gr_complex(0.980801, -0.19501),
	gr_complex(1.0, 1.2e-05), gr_complex(0.980785, 0.195092), gr_complex(0.923879, 0.382684), gr_complex(0.83147, 0.55557),
	gr_complex(0.707107, 0.707107), gr_complex(0.55557, 0.83147), gr_complex(0.382684, 0.923879), gr_complex(0.195092, 0.980785),
	gr_complex(1.2e-05, 1.0), gr_complex(-0.19501, 0.980801), gr_complex(-0.38225, 0.924059), gr_complex(-0.553737, 0.832692),
	gr_complex(-0.701059, 0.713104), gr_complex(-0.815998, 0.578055), gr_complex(-0.893407, 0.449249), gr_complex(-0.934886, 0.354949),
	gr_complex(-0.947363, 0.320163), gr_complex(-0.934914, 0.354874), gr_complex(-0.893617, 0.44883), gr_complex(-0.817269, 0.576256),
	gr_complex(-0.707107, 0.707107), gr_complex(-0.576256, 0.817269), gr_complex(-0.44883, 0.893617), gr_complex(-0.354873, 0.934914),
	gr_complex(-0.320157, 0.947364), gr_complex(-0.354911, 0.9349), gr_complex(-0.449039, 0.893512), gr_complex(-0.577156, 0.816634),
	gr_complex(-0.710112, 0.704089), gr_complex(-0.825057, 0.565049), gr_complex(-0.909448, 0.415819), gr_complex(-0.961187, 0.275898)
      };

      // Do <+signal processing+>
      for(i=0; i<noutput_items/256; i++)
      {
        float dp = in[i]?d_dp:-d_dp;
        for(j=0; j<256; j++)
        {
          out[i*256+j] = asm32[j] * gr_expj(d_pacc);

          d_pacc = d_pacc + dp;

          if(d_pacc > M_PI)
          {
	          d_pacc -= 2.0f*M_PI;
          }
          else if(d_pacc < -M_PI)
          {
	          d_pacc += 2.0f*M_PI;
          }
        }
      }    

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace dslwp */
} /* namespace gr */

