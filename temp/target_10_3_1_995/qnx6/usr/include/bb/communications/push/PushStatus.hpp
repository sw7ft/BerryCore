/*
 * (C) 2011-2012 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 *
 * PushStatus.hpp
 *
 *  Created on: Oct 25, 2011
 *      Author: rtalwalkar
 *
 * @since 10.0.0
 */

#ifndef BB_COMMUNICATIONS_PUSH_PUSHSTATUS_HPP_
#define BB_COMMUNICATIONS_PUSH_PUSHSTATUS_HPP_

#include <string>
#include <bb/communications/push/PushErrno.hpp>

namespace bb {
namespace communications {
namespace push {
class PushStatusPrivate;

class PushStatus {
public:
    /** Constructor for PushStatus object
     *
     * @return PushStatus object
     *
     * @since 10.0.0
     */
    PushStatus();

    /** constructor for PushStatus object
     *
     * @param code     Code associated with the status
     *
     * @since 10.0.0
     */
    explicit PushStatus(int code);

    /**
	 * Creates a copy of of an existing @c PushStatus object.
	 *
	 * @param other The existing @c PushStatus object that will be copied.
	 *
	 * @since 10.0.0
	 */
    PushStatus(const PushStatus &other);

    /** Destructor for PushStatus object
     *
     * @since 10.0.0
     */
    ~PushStatus();

    /**
	 * Copies the data from an existing @c PushStatus object.
	 *
	 * @param rhs The existing @c PushStatus object that will be copied.
	 *
	 * @since 10.0.0
	 */
    PushStatus& operator=(const PushStatus &rhs);

    /** Get the return code associated with the PushStatus object
     *
     * @return code    Returns the code associated with the PushStatus
     *                      0 means success
     *                      Otherwise failure.  ErrorDescription provides additional
     *                      information
     *
     * @since 10.0.0
     */
    int getCode() const;

    /** Gets the error description associated with the PushStatus object
     *
     * @return errorDescription    Provides additional information on the error.
     * 							   Empty string in case of success.
     *
     * @since 10.0.0
     */
    const std::string& getErrorDescription() const;

    /** Setter for status code
     *
     * @param code     Code associated with the status
     *
     * @since 10.0.0
     */
    void setCode(int code);

    /** Setter for status code
     *
     * @param errorDescription     Error details associated with the status
     *
     * @since 10.0.0
     */
    void setErrorDescription(const std::string& errorDescription);

    /**
     * @return	true if there is an error
     * 			false otherwise
     *
     * @since 10.0.0
     */
    bool isError() const;

private:
    PushStatusPrivate *d_ptr;
};
} // namespace push
} // namespace communications
} // namespace bb

#endif /* BB_COMMUNICATIONS_PUSH_PUSHSTATUS_HPP_ */
