/**
 * @file Dissector.h
 *
 * @brief The Basic Dissector abstraction (Interface).
 *
 * The Base Dissector abstraction. Every implementation of a Dissector will use
 * and implement the operations described in this interface.
 * Dissector are used to dissect certain ranges of data in a network package,
 * while having the possibility to link to further dissectors when the dissection
 * of the desired range is complete.
 *
 * -> It is possible to link several Dissectors together building a tree of dissectors
 * and subdissectors that call each other when their dissection part is completed.
 */

#include <stdlib.h>
#include <stdint.h>

#include "ProtocolTree.h"
#include "Buffy.h"


#include "Dissector.h"
#include "Dissector-int.h"

#include "dissect/DissectorRegister-int.h"
#include "dissect/DissectorRegister.h"

#include "dbg.h"

Dissector_t * Dissector_new(const struct Dissector_ops *ops) {

	Dissector_t *dissector = malloc(sizeof(Dissector_t));
	check_mem(dissector);

	dissector->dissectorRegister = DissectorRegister_new();
	check_mem(dissector->dissectorRegister);

	dissector->ops = ops;

	return dissector;

error:
	return NULL;
}

void Dissector_free(Dissector_t *dissector) {

	dissector->dissectorRegister->ops->DissectorRegister_free(dissector->dissectorRegister);

	free(dissector);
}


Dissector_t * Dissector_registerSub(Dissector_t *this,
                           Dissector_t *subDissector) {

	DissectorRegister_t *thisRegister = this->dissectorRegister;

	Dissector_t *existing = this->dissectorRegister->ops->DissectorRegister_insert(thisRegister, subDissector);

	// TODO implement proper error testing and duplicates with insertion

	return existing;
}

Dissector_t * Dissector_getSub(Dissector_t *this, uint64_t data) {

	return this->dissectorRegister->ops->DissectorRegister_get(this->dissectorRegister, data);

}

/**
int Dissector_dissect(Dissector_t *this, Buffy_t *buf, ProtocolTree_t *tree) {



}
*/