#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "config.h"
#include "caudio.h"
// We'll be using an RTPSession instance from the JRTPLIB library. The following
// function checks the JRTPLIB error code.

CAudio::CAudio() //: m_chain("MainAudio")
{

#ifdef WIN32
    WSADATA dat;
    WSAStartup(MAKEWORD(2,2),&dat);
#endif // WIN32
    MIPAudioSession asSess;
    MIPAudioSessionParams* asParams = new MIPAudioSessionParams();
    asParams->setPortbase(AUDIO_PORTBASE);
    if(!asParams->getInputDeviceID() || !asParams->getOutputDeviceID())
    {
        std::cerr << "No input device dected!\n";
        exit(1);
    }
    asParams->setAcceptOwnPackets(true);
    asParams->setCompressionType(MIPAudioSessionParams::CompressionType::ULaw);
    if(!asSess.init(asParams))
    {
        std::cerr << "Error initializing session";
        exit(1);
    }
    asSess.setReceiveMode(jrtplib::RTPTransmitter::AcceptAll);
    asSess.addDestination(jrtplib::RTPIPv4Address((uint32_t)inet_addr("127.0.0.1"), AUDIO_PORTBASE)); //localhost
    if(!asSess.init(asParams))
    {
        std::cout << "Error inititalzing session";
        exit(1);
    }
        return;
}

CAudio::CAudio(uint8_t* ipaddr, int port) //: m_chain("MainAudio")
{
#ifdef WIN32
    WSADATA dat;
    WSAStartup(MAKEWORD(2,2),&dat);
#endif // WIN32
    MIPTime interval(0.020); // We'll use 20 millisecond intervals.
    MIPAverageTimer timer(interval);
    MIPWAVInput sndFileInput;
    MIPSamplingRateConverter sampConv, sampConv2;
    MIPSampleEncoder sampEnc, sampEnc2, sampEnc3;
    MIPULawEncoder uLawEnc;
    MIPRTPULawEncoder rtpEnc;
    MIPRTPComponent rtpComp;
    MIPRTPDecoder rtpDec;
    MIPRTPULawDecoder rtpULawDec;
    MIPULawDecoder uLawDec;
    MIPAudioMixer mixer;
    MIPPAInputOutput sndCardOutput;
#ifndef WIN32
    MIPOSSInputOutput sndCardOutput;
#else
    //MIPWinMMOutput sndCardOutput;
#endif
    MIPComponentChain chain("Sound file player");
    jrtplib::RTPSession rtpSession;
    bool returnValue;
    // We'll open the file 'soundfile.wav'.
    returnValue = sndFileInput.open("soundfile.wav", interval);
    checkError(returnValue, sndFileInput);
    // We'll convert to a sampling rate of 8000Hz and mono sound.
    int samplingRate = 8000;
    int numChannels = 1;
    returnValue = sampConv.init(samplingRate, numChannels);
    checkError(returnValue, sampConv);
    // Initialize the sample encoder: the RTP U-law audio encoder
    // expects native endian signed 16 bit samples.
    returnValue = sampEnc.init(MIPRAWAUDIOMESSAGE_TYPE_S16);
    checkError(returnValue, sampEnc);
    // Convert samples to U-law encoding
    returnValue = uLawEnc.init();
    checkError(returnValue, uLawEnc);
    // Initialize the RTP audio encoder: this component will create
    // RTP messages which can be sent to the RTP component.
    returnValue = rtpEnc.init();
    checkError(returnValue, rtpEnc);
    // We'll initialize the RTPSession object which is needed by the
    // RTP component.
    jrtplib::RTPUDPv4TransmissionParams transmissionParams;
    jrtplib::RTPSessionParams sessionParams;
    int portBase = AUDIO_PORTBASE;
    int status;
    transmissionParams.SetPortbase(portBase);
    sessionParams.SetOwnTimestampUnit(1.0/((double)samplingRate));
    sessionParams.SetMaximumPacketSize(64000);
    sessionParams.SetAcceptOwnPackets(true);
    status = rtpSession.Create(sessionParams,&transmissionParams);
    checkError(status);
    // Instruct the RTP session to send data to ourselves.
    status = rtpSession.AddDestination(jrtplib::RTPIPv4Address(ntohl(inet_addr("127.0.0.1")),portBase));
    checkError(status);
    // Tell the RTP component to use this RTPSession object.
    returnValue = rtpComp.init(&rtpSession);
    checkError(returnValue, rtpComp);
    // Initialize the RTP audio decoder.
    returnValue = rtpDec.init(true, 0, &rtpSession);
    checkError(returnValue, rtpDec);
    // Register the U-law decoder for payload type 0
    returnValue = rtpDec.setPacketDecoder(0,&rtpULawDec);
    checkError(returnValue, rtpDec);
    // Convert U-law encoded samples to linear encoded samples
    returnValue = uLawDec.init();
    checkError(returnValue, uLawDec);
    // Transform the received audio data to floating point format.
    returnValue = sampEnc2.init(MIPRAWAUDIOMESSAGE_TYPE_FLOAT);
    checkError(returnValue, sampEnc2);
    // We'll make sure that received audio frames are converted to the right
    // sampling rate.
    returnValue = sampConv2.init(samplingRate, numChannels);
    checkError(returnValue, sampConv2);
    // Initialize the mixer.
    returnValue = mixer.init(samplingRate, numChannels, interval);
    checkError(returnValue, mixer);
    // Initialize the soundcard output.
    returnValue = sndCardOutput.open(samplingRate, numChannels, interval);
    checkError(returnValue, sndCardOutput);
#ifndef WIN32
    // The OSS component can use several encodings. We'll check
    // what encoding type is being used and inform the sample encoder
    // of this.
    uint32_t audioSubtype = sndCardOutput.getRawAudioSubtype();
    returnValue = sampEnc3.init(audioSubtype);
#else
    // The WinMM soundcard output component uses 16 bit signed little
    // endian data.
    returnValue = sampEnc3.init(MIPRAWAUDIOMESSAGE_TYPE_S16LE);
#endif
    checkError(returnValue, sampEnc3);
    // Next, we'll create the chain
    returnValue = chain.setChainStart(&timer);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&timer, &sndFileInput);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&sndFileInput, &sampConv);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&sampConv, &sampEnc);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&sampEnc, &uLawEnc);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&uLawEnc, &rtpEnc);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&rtpEnc, &rtpComp);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&rtpComp, &rtpDec);
    checkError(returnValue, chain);
    // This is where the feedback chain is specified: we want
    // feedback from the mixer to reach the RTP audio decoder,
    // so we'll specify that over the links in between, feedback
    // should be transferred.
    returnValue = chain.addConnection(&rtpDec, &uLawDec, true);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&uLawDec, &sampEnc2, true);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&sampEnc2, &sampConv2, true);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&sampConv2, &mixer, true);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&mixer, &sampEnc3);
    checkError(returnValue, chain);
    returnValue = chain.addConnection(&sampEnc3, &sndCardOutput);
    checkError(returnValue, chain);
    // Start the chain
    returnValue = chain.start();
    checkError(returnValue, chain);
    // We'll wait until enter is pressed
    getc(stdin);
    returnValue = chain.stop();
    checkError(returnValue, chain);
    rtpSession.Destroy();}       //Ne fonctionne pas no idea pk

CAudio::~CAudio()
{
    m_session.destroy();
    /*int returnValue = m_chain.stop();
    checkError(returnValue, m_chain);
    m_rtp.destroy();*/
#ifdef WIN32
    WSACleanup();
#endif
}



void CAudio::checkError(bool returnValue, const MIPComponent &component)
{
    if (returnValue)
        return;
    std::cerr << "An error occured in component: " << component.getComponentName() << std::endl;
    std::cerr << "Error description: " << component.getErrorString() << std::endl;
    exit(-1);
}
void CAudio::checkError(bool returnValue, const MIPComponentChain &chain)
{
    if (returnValue == true)
        return;
    std::cerr << "An error occured in chain: " << chain.getName() << std::endl;
    std::cerr << "Error description: " << chain.getErrorString() << std::endl;
    exit(-1);
}
void CAudio::checkError(int status)
{
    if (status >= 0)
        return;
    std::cerr << "An error occured in the RTP component: " << std::endl;
    std::cerr << "Error description: " << jrtplib::RTPGetErrorString(status) << std::endl;
    exit(-1);
}

void CAudio::onThreadExit(bool error, const std::string &errorComponent, const std::string &errorDescription)
{
    if (!error)
        return;
    std::cerr << "An error occured in the background thread." << std::endl;
    std::cerr << "    Component: " << errorComponent << std::endl;
    std::cerr << "    Error description: " << errorDescription << std::endl;
}

