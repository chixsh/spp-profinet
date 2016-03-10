#ifndef __BLOCK_DISSECTOR_H__
#define __BLOCK_DISSECTOR_H__

/**
 * @file
 * @brief BlockDissector header.
 *
 * This Dissector ist the dissector for asynchronous real time
 *
 */


#include <stdlib.h>
#include <stdio.h>

#include "dissect/Dissector-int.h"
#include "dissect/Dissector.h"
#include "dissect/tree/ProtocolTree.h"
#include "dissect/buffer/Buffy.h"

#define BLOCK_DISSECTOR_ID      0xffffffffffffffff

/**
 * @see Dissector_new
 */
Dissector_t *BlockDissector_new();

/**
 * @see Dissector_free
 */
void BlockDissector_free(Dissector_t *dissector);

/**
 * @see Dissector_dissect
 */
int BlockDissector_dissect(Dissector_t *this, Buffy_t *buf, ProtocolTree_t *tree);

#endif
