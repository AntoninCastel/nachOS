#ifndef __FRAMEPROVIDER_H__
#define __FRAMEPROVIDER_H__

#include <ctime>
#include "bitmap.h"

typedef enum {
    FIRST_FREE_FRAME,
    RANDOM_FREE_FRAME
} allocation_policy;

class FrameProvider {
public:
    FrameProvider(int nb_frames, allocation_policy policy = FIRST_FREE_FRAME);
    ~FrameProvider();

    int     GetEmptyFrame();
    void    ReleaseFrame(int frame_id);
    int     NumAvailFrame();

private:
    int                 m_nb_frames;
    BitMap*             m_frames;
    allocation_policy   m_alloc_policy;

    // Allocation Policies
    int first_free_frame();
    int random_free_frame();
};

#endif
