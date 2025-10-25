/*!
 * @copyright
 * Copyright (C) 2012 - 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_LINE_HPP
#define BB_SYSTEM_PHONE_LINE_HPP


#include <bb/system/phone/LineType>
#include <bb/system/Global>
#include <QSharedDataPointer>

namespace bb
{
namespace system
{
namespace phone
{

class LinePrivate;

/*!
 * @headerfile Line.hpp <bb/system/phone/Line>
 *
 * @brief Provides a phone line's ID, address, and type information.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @permissions You must also specify the @c access_phone permission in your bar-descriptor.xml file.
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT Line
{
public:
    /*!
     * @brief Creates a new @c Line object.
     *
     * @since BlackBerry 10.0.0
     */
    Line();

    /*!
     * @brief Creates a copy of a @c Line.
     *
     * @param other The source @c Line object.
     *
     * @since BlackBerry 10.0.0
     */
    Line(const Line &other);

    /*!
     * @brief Destroys this @c Line object.
     *
     * @since BlackBerry 10.0.0
     */
    ~Line();

    /*!
     * @brief Copies another @c Line to this object.
     *
     * @param other The source @c Line object.
     * @return The @c Line instance.
     *
     * @since BlackBerry 10.0.0
     */
    Line& operator=(const Line &other);

    /*!
     * @brief Compares another @c Line to this object.
     *
     * @param other A @c Line object for comparison.
     * @return @c true if the type and address match, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const Line &other);

    /*!
     * @brief Returns the ID of the line.
     *
     * @return The line ID. If the line is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    QString id() const;

    /*!
     * @brief Returns the type of the line, as specified by @c LineType.
     *
     * @return The line type. If the line is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    LineType::Type type() const;

    /*!
     * @brief Returns a brief description of the line.
     *
     * @return The line description. If the line is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    QString description() const;

    /*!
     * @brief Returns the line's address.
     *
     * For a cellular line, the line address is the phone number. For a video chat line, the address is
     * the PIN of the device.
     *
     * @return The line address. If the line is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    QString address() const;

    /*!
     * @brief Indicates whether the line is valid or not.
     *
     * Typically, this function should be called to ensure the line is valid
     * before other member functions of this class are called.
     *
     * @return Returns @c true if the line is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    //!@cond PRIVATE
    friend class LinePrivate;

    Line(const QSharedDataPointer<LinePrivate> &d_other);

    QSharedDataPointer<LinePrivate> d_ptr;   /**< private implementation */
    //!@endcond
};

} // phone
} // system
} // bb

Q_DECLARE_METATYPE(bb::system::phone::Line);

#endif /* BB_SYSTEM_PHONE_LINE_HPP */
