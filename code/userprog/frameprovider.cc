#include "frameprovider.h"

FrameProvider::FrameProvider(int nb_frames, allocation_policy policy) {
    srand(time(NULL));
    m_frames = new BitMap(nb_frames);
    m_alloc_policy = policy;
    m_nb_frames = nb_frames;
}

FrameProvider::~FrameProvider() {
    delete m_frames;
}

int FrameProvider::GetEmptyFrame() {
    switch(m_alloc_policy) {
    case FIRST_FREE_FRAME:  return first_free_frame();
    case RANDOM_FREE_FRAME: return random_free_frame();
    default:    return -1;
    }
}

void FrameProvider::ReleaseFrame(int frame_id) {
    m_frames->Clear(frame_id);
}

int FrameProvider::NumAvailFrame() {
    return m_frames->NumClear();
}

int FrameProvider::first_free_frame() {
    return m_frames->Find();
}

int FrameProvider::random_free_frame() {
    int frame;
    if(m_frames->NumClear() > 0) {
        do {
            frame = rand() % m_nb_frames;
        } while(m_frames->Test(frame));
        m_frames->Mark(frame);
    } else {
        frame = -1;
    }
    return frame;
}
