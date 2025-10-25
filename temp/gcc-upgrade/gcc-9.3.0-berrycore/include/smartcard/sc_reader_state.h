/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file sc_reader_state.h
 *
 * Reader state instances are used to store state information about individual
 * smart card readers. Information stored in a reader state instance includes:
 *
 * - the name of a smart card reader
 * - the state of a smart card reader as known at present time, otherwise known
 *   as the current state
 * - the state of a smart card reader in response to some event, otherwise known
 *   as the event state
 *
 * The main purpose of the reader state is to help identify changes in reader state.
 * This is done by comparing the event and current state values. If these values
 * are different, then a change has occurred with the updated reader state being
 * reflected in the event state value.
 */


#ifndef SC_READER_STATE_H
#define SC_READER_STATE_H

#include <smartcard/sc_data_types.h>

#include <sys/platform.h>


__BEGIN_DECLS


/**
 * Smart card state represents the state of a smart card in a reader.
 */
typedef struct _sc_reader_state_t sc_reader_state_t;


/**
 * Creates @c sc_reader_state_t instance.
 * To destroy the instance, use @c sc_reader_state_destroy() function.
 *
 * @param [out] reader_state
 *      Created reader state instance. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reader_state_create( sc_reader_state_t** reader_state );


/**
 * Destroys @c sc_reader_state_t instance.
 *
 * @param [in] reader_state
 *      Reader state instance to be destroyed. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reader_state_destroy( sc_reader_state_t* reader_state );


/**
 * Gets the current state value.
 *
 * @param [in] reader_state
 *      Reader state instance. Must not be NULL.
 * @param [out] current_state
 *      Current reader state. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reader_state_get_current_state( const sc_reader_state_t* reader_state,
                                                      sc_reader_state_value_t* current_state );


/**
 * Sets the current state value.
 *
 * @param [in,out] reader_state
 *      Reader state instance. Must not be NULL.
 * @param [in] current_state
 *      Current reader state.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reader_state_set_current_state( sc_reader_state_t* reader_state,
                                                      sc_reader_state_value_t current_state );


/**
 * Gets the event state value.
 *
 * @param [in] reader_state
 *      Reader state instance. Must not be NULL.
 * @param [out] event_state
 *      Reader event state. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reader_state_get_event_state( const sc_reader_state_t* reader_state,
                                                    sc_reader_state_value_t* event_state );


/**
 * Sets the event state value.
 *
 * @param [in,out] reader_state
 *      Reader state instance. Must not be NULL.
 * @param [in] event_state
 *      Reader event state.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reader_state_set_event_state( sc_reader_state_t* reader_state,
                                                    sc_reader_state_value_t event_state );


/**
 * Gets the reader name.
 *
 * @param [in] reader_state
 *      Reader state instance. Must not be NULL.
 * @param [out] reader_name
 *      Reader name. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reader_state_get_reader_name( const sc_reader_state_t* reader_state,
                                                    const sc_reader_name_t** reader_name );


/**
 * Sets the reader name.
 *
 * @param [in,out] reader_state
 *      Reader state instance. Must not be NULL.
 * @param [in] reader_name
 *      Reader name.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reader_state_set_reader_name( sc_reader_state_t* reader_state,
                                                    const sc_reader_name_t* reader_name );


__END_DECLS

#endif /* SC_READER_STATE_H */
