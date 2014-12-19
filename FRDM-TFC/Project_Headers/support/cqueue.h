/**
 * @file cqueue.h
 *
 * @brief Ring buffers
 *
 * Ringbuffer implementation store/access acditrary binary data
 *
 * @todo allow to register i/o filters to be executed at read/write time
 *
 */

#ifndef __CQ_H__
#define __CQ_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* OVERWRITE MODE NOT IMPLEMENTED
 * 
typedef enum {
    RBUF_MODE_BLOCKING = 0,
    RBUF_MODE_OVERWRITE
} cqueue_mode_t;
*/

typedef struct {
    void* *buf;              // queue elements
    uint32_t size;           // queue size
    uint32_t available;      // queue size
    uint32_t used;           // used size
    uint32_t rfx;            // read offset
    uint32_t wfx;            // write offset
  //uint32_t mode;           // the queue mode (blocking/overwrite)
} cqueue_s;

void      cqueue_init(cqueue_s *cq, void* *buf, uint32_t size);
//void      cqueue_set_mode(cqueue_s *cqueue, cqueue_mode_t mode);
//cqueue_mode_t cqueue_mode(cqueue_s *cqueue);
void      cqueue_skip(cqueue_s *cq, uint32_t size);
uint32_t  cqueue_pop(cqueue_s *cq, void* *out, uint32_t size);
uint32_t  cqueue_push(cqueue_s *cq, void* *in, uint32_t size);
uint32_t  cqueue_size(cqueue_s *cq);
uint32_t  cqueue_used(cqueue_s *cq);
uint32_t  cqueue_available(cqueue_s *cq);
void      cqueue_clear(cqueue_s *cq);

#ifdef __cplusplus
}
#endif

#endif

// vim: tabstop=4 shiftwidth=4 expandtab:
/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
