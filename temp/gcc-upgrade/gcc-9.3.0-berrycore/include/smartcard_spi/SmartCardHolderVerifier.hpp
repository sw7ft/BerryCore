/*
 * SmartCardHolderVerifier.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDHOLDERVERIFIER_HPP
#define SMARTCARD_SPI_SMARTCARDHOLDERVERIFIER_HPP


#include <smartcard_spi/SmartCardInterface.hpp>


namespace smartcard_spi
{

/**
 * @c SmartCardHolderVerifier interface defines functionality used to access chip
 * holder verification (CHV) related services provided by the smart card. This
 * provides applications the ability to force a CHV or to allow the user to
 * change a CHV code. This interface should be implemented as part of smart card
 * cryptographic service providers that expose CHV functionality.
 *
 * It is expected that applications will allow the service provider to determine
 * when CHV is required and prompt the user. Similarly, it is expected that
 * CHV administration will be under user control and will be performed using a
 * service provider-implemented user interface.
 */
class SmartCardHolderVerifier : public SmartCardInterface
{

public:

    /**
     * Destructor.
     */
    virtual ~SmartCardHolderVerifier();


    /**
     * Changes smart card PIN.
     *
     * @param [in] oldCode
     *      Current PIN.
     * @param [in] oldCodeLength
     *      Current PIN length.
     * @param [in] newCode
     *      New PIN.
     * @param [in] newCodeLength
     *      New PIN length.
     * @param [in] flags
     *      Indicates whether the CHV is to be made against a local (@c SC_FL_IHV_LOCAL)
     *      or global (@c SC_FL_IHV_GLOBAL) code.
     *      If the @c SC_FL_IHV_CHECKONLY flag is specified, a pop-up dialogue requesting
     *      input of CHV information should not be presented; instead, only the CHV state
     *      should be returned.
     * @param [in] ref
     *      Vendor-specific reference value.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t changeCode( const unsigned char* oldCode,
                                           unsigned int oldCodeLength,
                                           const unsigned char* newCode,
                                           unsigned int newCodeLength,
                                           unsigned int flags,
                                           unsigned int ref );


    /**
     * Retrieves the maximum number of PIN attempts for the current card.
     *
     * @param [out] maxNumAttempts
     *      Maximum number of PIN attempts for the current card.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getMaximumNumberOfPinAttempts( unsigned int& maxNumAttempts );


    /**
     * Retrieves the number of PIN attempts remaining for the current card.
     *
     * @param [out] attemptsRemaining
     *      Number of PIN attempts remaining for the current card.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getNumberOfPinAttemptsRemaining( unsigned int& numAttemptsRemaining );


    /**
     * Forces a card holder verification against the card.
     *
     * If a code is supplied, it is used to verify to the card.
     * If no code is supplied, then the user will be prompted for a code.
     * Note that if the CHV requirements for the currently selected path are
     * satisfied (by a prior CHV), the service provider may simply return success.
     *
     * @param [in] code
     *      Code used to verify the user to the card.
     *      If null, user will be prompted for a code.
     * @param [in] codeLength
     *      Code length.
     * @param [in] flags
     *      Indicates whether the CHV is to be made against a local (@c SC_FL_IHV_LOCAL)
     *      or global (@c SC_FL_IHV_GLOBAL) code.
     *      If the @c SC_FL_IHV_CHECKONLY flag is specified, a pop-up dialogue requesting
     *      input of CHV information should not be presented; instead, only the CHV state
     *      should be returned.
     * @param [in,out] ref
     *      A vendor-specific reference value.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t verify( const unsigned char* code,
                                       unsigned int codeLength,
                                       unsigned int flags,
                                       unsigned int& ref );


    /**
     * Cancels any outstanding verify operations.
     *
     * @param [in] forceCancel
     *      If set to true, all in-progress verify operations must be terminated
     *      immediately. Otherwise, attempts to gracefully cancel all
     *      in-prorgress operations should be made where possible.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t cancelVerify( bool forceCancel );


    /**
     * Retrieves code information for the card.
     *
     * @param [in] flags
     *      Indicates whether the CHV info shoul be retrieved for a local (@c SC_FL_IHV_LOCAL)
     *      or global (@c SC_FL_IHV_GLOBAL) code.
     * @param [out] codeType
     *      Code type.
     * @param [out] minCodeLength
     *      Minimum code length. Negative value if unknown.
     * @param [out] maxCodeLength
     *      Maximum code length. Negative value if unknown.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getCodeInfo( unsigned int flags,
                                            sc_code_type_t& codeType,
                                            int& minCodeLength,
                                            int& maxCodeLength );


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardHolderVerifier();

};

}

#endif /* SMARTCARD_SPI_SMARTCARDHOLDERVERIFIER_HPP */

