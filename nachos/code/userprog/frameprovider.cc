#include "frameprovider.h"
#include "synch.h"

FrameProvider::FrameProvider(int nb_frames, allocation_policy policy) {
    m_lock = new Semaphore("FrameProvider", 1);
    srand(time(NULL));
    m_frames = new BitMap(nb_frames);
    m_alloc_policy = policy;
    m_nb_frames = nb_frames;
}

FrameProvider::~FrameProvider() {
    delete m_frames;
    delete m_lock;
}

int FrameProvider::GetEmptyFrame() {
    m_lock->P();
    int frame;
    switch(m_alloc_policy) {
    case FIRST_FREE_FRAME:
        frame = first_free_frame(); 
        break;
    case RANDOM_FREE_FRAME: 
        frame = random_free_frame();
        break;
    default:
        frame = -1;
    }
    //fprintf(stderr, "frame %d attribuée\n", frame);
    m_lock->V();
    return frame;
}

void FrameProvider::ReleaseFrame(int frame_id) {
    m_lock->P();
    m_frames->Clear(frame_id);
    m_lock->V();
}

int FrameProvider::NumAvailFrame() {
    m_lock->P();
    int nb_avail_frames = m_frames->NumClear();
    m_lock->V();
    return nb_avail_frames;
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
