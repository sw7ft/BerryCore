/*
 * SmartCardDataTypes.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDDATATYPES_HPP
#define SMARTCARD_SPI_SMARTCARDDATATYPES_HPP


#include <smartcard/sc_data_types.h>


namespace smartcard_spi
{
    /**
     * ATR string.
     */
    typedef unsigned char AtrString[ SC_MAX_ATR_LENGTH ];


    /**
     * A non-comprehensive set of IFD device protocol options.
     * These flags may be used for capability tags.
     */
    enum InterfaceDeviceProtocolOptionTag
    {
        /**
         * Current protocol type.
         * As single protocol must be defined for this value.
         */
        TAG_CURRENT_PROTOCOL_TYPE  = 0x0201,
    };


    /**
     * A non-comprehensive set of IFD ICC states.
     * These flags may be used for capability tags.
     */
    enum IccStateTag
    {
        /**
         * Indicates ICC presence status.
         *
         * 0 = not present
         * 1 = card present but not swallowed (applies only if the IFD supports ICC swallowing)
         * 2 = card present (and swallowed if the IFD supports ICC swallowing)
         * 4 = card confiscated
         */
        TAG_ICC_PRESENCE           = 0x0300,

        /**
         * ICC interface status.
         *
         * 0 = contact inactive
         * 1 = contact active
         */
        TAG_ICC_INTERFACE_STATUS   = 0x0301,

        /**
         * Contains the ATR string as returned by the IFD subsystem.
         */
        TAG_ICC_ATR_STRING         = 0x0303,

        /**
         * ICC type. The value should be ISO/IEC card or unknown.
         * 0 = unknown ICC type,
         * 1 = 7816 Asynchronous
         * 2 = 7816 Synchronous (unspecified)
         * 3 = 7816-10 Synchronous (Type 1)
         * 4 = 7816-10 Synchronous (Type 2)
         * 5 = 14443 (Type A)
         * 6 = 14443 (Type B)
         * 7 = ISO 15693
         * Other values RFU
         */
        TAG_ICC_TYPE               = 0x0304
    };


    /**
     * IFD power action.
     */
    enum IfdPowerAction
    {
        /**
         * For ISO/IEC 7816-compatible environment: requests activation of the contact.
         *
         * For contact-less environment:
         * No effect if a PICC is active in the slot logical device.
         * Error condition otherwise.
         */
        IFD_POWER_UP          = 0x01,

        /**
         * For ISO/IEC 7816-compatible environment: Requests deactivation of the contact.
         *
         * For contact-less environment:
         *  - ISO 14443-4: DESELECT the PICC. No card removal notification must be generated.
         *    Poll for the PICC at ISO 14443-3 level. Keep the slot logically occupied.
         *  - ISO 15693 / ISO 14443-3: No state change since these cards are only active during
         *    communication and halted otherwise. Do not generate a removal event.
         */
        IFD_POWER_DOWN        = 0x02,

        /**
         * For ISO/IEC 7816-compatible environment: Requests a warm reset of the ICC.
         *
         * For contact-less environment:
         *  - ISO 14443-4: DESELECT the PICC and reactivate it in the same slot logical device.
         *    No card removal notification must be generated.
         *    When already powered down (see previous): Reactivate the PICC.
         *  - ISO 15693 / 14443-3: No action required since these cards remain in HALT and are
         *    only reactivated for communication.
         */
        IFD_RESET             = 0x03,

        /**
         * For ISO/IEC 7816-compatible environment: Requests a cold reset of the ICC.
         *
         * For contact-less environment: Same as for warm reset.
         */
        IFD_COLD_RESET        = 0x04,

        /**
         * No power changes are required, but the reader is notified that it may be
         * be entering an idle state. This flag is used when a client session has ended.
         *
         * The flag is not part of PC/SC specification.
         */
        IFD_LEAVE_CARD        = 0x05,

        /**
         * Requests the reader to maintain power to the card even though the reader
         * may be entering an idle state.
         * The flag is typically used when a client session has ended, but the client
         * requested to keep the card powered to maintain the smart card state.
         *
         * The flag is not part of PC/SC specification.
         */
        IFD_KEEP_CARD_POWERED = 0x06
    };


    /**
     * IfdState is used to indicate the state of the card in the reader and the current
     * protocol status of the card. For the latter, this is used to specify whether the
     * card is willing to negotiate a new protocol or not as defined in ISO/IEC 7816.
     */
    enum IfdState
    {
        /**
         * State is not known.
         */
        SCARD_UNKNOWN        = 0x00000001,

        /**
         * No card is in the reader.
         */
        SCARD_ABSENT         = 0x00000002,

        /**
         * A card is in the reader.
         */
        SCARD_PRESENT        = 0x00000004,

        /**
         * A card is in the reader and is properly positioned for operation.
         */
        SCARD_SWALLOWED      = 0x00000008,

        /**
         * A card is in the reader and has been powered.
         */
        SCARD_POWERED        = 0x00000010,

        /**
         * The card is capable of negotiating a new protocol setting.
         */
        SCARD_NEGOTIABLEMODE = 0x00000020,

        /**
         * The card is in a specific protocol mode and a new protocol may not be negotiated.
         */
        SCARD_SPECIFICMODE   = 0x00000040
    };


    /**
     * Selection flags indicate which of the optional parameters (PPS1, PPS2 and PPS3), if any,
     * have to be negotiated and included in the PPS request. It is obtained by performing a
     * bitwise OR operation on the flags.
     */
    enum IfdPpsParameterSelectionFlag
    {
        IFD_NEGOTIATE_PPS1 = 1,
        IFD_NEGOTIATE_PPS2 = 2,
        IFD_NEGOTIATE_PPS3 = 4
    };
}

#endif /* SMARTCARD_SPI_SMARTCARDDATATYPES_HPP */
