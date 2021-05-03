/*
    
  This file is a part of EMIPLIB, the EDM Media over IP Library.
  
  Copyright (C) 2006-2016  Hasselt University - Expertise Centre for
                      Digital Media (EDM) (http://www.edm.uhasselt.be)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  
  USA

*/

#ifndef MIPCONFIG_H

#define MIPCONFIG_H

#define EMIPLIB_IMPORT __declspec(dllimport)
#define EMIPLIB_EXPORT __declspec(dllexport)
#ifdef EMIPLIB_COMPILING
	#define EMIPLIB_IMPORTEXPORT EMIPLIB_EXPORT
#else
	#define EMIPLIB_IMPORTEXPORT EMIPLIB_IMPORT
#endif // EMIPLIB_COMPILING

// No GPL components will be compiled

// Little endian system

// No libsndfile support

// No libaudiofile support

// No support for Qt5 output components

// No ALSA support

// No Speex support

#define MIPCONFIG_SUPPORT_GSM

#define MIPCONFIG_SUPPORT_LPC

// No libavcodec support

// No support for Intel IPP library

// No support for ESD based output

// No support for JACK audio input/output

// No support for Video4Linux

// No support for OSS

// No support for SDL audio output

// No OpenAL output support

#define MIPCONFIG_SUPPORT_PORTAUDIO

// No support for AudioTrack output component

// No support for AudioRecorder input component

//No support for MIPCONFIG_SUPPORT_WINMM

// No support for DirectShow video input codec

// No support for SILK codec

// No Opus support

// No support for PulseAudio input/output

// No support for OpenSL ES on Android

#ifdef MIPCONFIG_SUPPORT_AVCODEC
	#ifndef __STDC_CONSTANT_MACROS
	#define __STDC_CONSTANT_MACROS
	#endif // __STDC_CONSTANT_MACROS
#endif // MIPCONFIG_SUPPORT_AVCODEC

#endif // MIPCONFIG_H

