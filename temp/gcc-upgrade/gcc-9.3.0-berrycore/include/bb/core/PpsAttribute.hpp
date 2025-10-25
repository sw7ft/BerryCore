/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PPSATTRIBUTE_HPP
#define BB_CORE_PPSATTRIBUTE_HPP

#include <bb/Global>
#include <bb/PpsAttributeFlag>

#include <QList>
#include <QMap>
#include <QSharedDataPointer>
#include <QVariant>

namespace bb
{
class PpsAttributePrivate;

/*!
 * @headerfile PpsAttribute.hpp <bb/PpsAttribute>
 *
 * @brief The @c %PpsAttribute class encapsulates a PPS attribute.
 *
 * Example:
 * @code
 * bb::PpsObject ppsObject("/pps/somepath");
 * ppsObject.open(bb::PpsOpenMode::Subscribe);
 * QByteArray rawData = ppsObject.read();
 * QMap<QString, bb::PpsAttribute> ppsData = bb::PpsObject::decodeWithFlags(rawData);
 * bb::PpsAttribute rootObject = ppsData.value("@somepath");
 * ...
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT PpsAttribute
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Attribute encoding types.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief The attribute has no type because the @c PpsAttribute is invalid.
         *
         * @since BlackBerry 10.0.0
         */
        None   = 0,

        /*!
         * @brief The attribute was encoded as a number (e.g., <code>"attr:n:10"</code>).
         *
         * @since BlackBerry 10.0.0
         */
        Number = 1,

        /*!
         * @brief The attribute was encoded as a Boolean (e.g., <code>"attr:b:false"</code>).
         *
         * @since BlackBerry 10.0.0
         */
        Bool   = 2,

        /*!
         * @brief The attribute was encoded as a string (e.g., <code>"attr::value"</code>).
         *
         * @since BlackBerry 10.0.0
         */
        String = 3,

        /*!
         * @brief The attribute was encoded as a JSON array (e.g., <code>"attr:json:[10, 20]"</code>).
         *
         * @since BlackBerry 10.0.0
         */
        Array  = 4,

        /*!
         * @brief The attribute was encoded as a PPS or JSON object (e.g., <code>"attr:json: { "key":10 }"</code>).
         *
         * @details This type is also used if the flags for this attribute include @c bb::PpsAttributeFlag::Deleted,
         * since the actual type of a deleted attribute cannot be determined.  The map associated with the attribute
         * will be empty.
         *
         * @since BlackBerry 10.0.0
         */
        Object = 5
    };

    /*!
     * @brief Creates an invalid @c PpsAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    PpsAttribute();

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~PpsAttribute();

    /*!
     * @brief Copy constructor.
     *
     * @details Creates a copy of a @c PpsAttribute.
     *
     * @param other The @c PpsAttribute to copy.
     *
     * @since BlackBerry 10.0.0
     */
    PpsAttribute(const PpsAttribute & other);

    /*!
     * @brief Assignment operator.
     *
     * @details Assigns a copy of a @c PpsAttribute.
     *
     * @param other The source @c PpsAttribute.
     * @return The @c PpsAttribute instance.
     *
     * @since BlackBerry 10.0.0
     */
    PpsAttribute &operator=(const PpsAttribute & other);

    /*!
     * @brief Equality operator.
     *
     * @details Attributes of different types are not equal. For example, Number/10.0 and String/10.0 are not equal.
     *
     * @param other The @c PpsAttribute to compare to.
     * @return @c true if the @c other has the same @c type(), @c flags(), and value; @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const PpsAttribute & other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details Attributes of different types are not equal. For example, Number/10.0 and String/10.0 are not equal.
     *
     * @param other The @c PpsAttribute to compare to.
     * @return @c true if @c other has a different @c type(), @c flags(), or value; @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const PpsAttribute & other) const;

    /*!
     * @brief Whether this @c PpsAttribute object contains valid information about a PPS attribute.
     *
     * @return @c true if this @c PpsAttribute object contains valid information about a PPS attribute; @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Gets the type of the PPS attribute.
     *
     * @return The type of the PPS attribute.
     *
     * @since BlackBerry 10.0.0
     */
    Type type() const;

    /*!
     * @brief Gets the PPS attribute's flags.
     *
     * @see @c PpsAttributeFlag
     *
     * @details If the returned flags include @c bb::PpsAttributeFlag::Deleted, the type for this
     * attribute will always be @c bb::PpsAttribute::Object with an empty map, since the actual type
     * of the deleted attribute cannot be determined.
     *
     * @return The PPS attribute's flags.
     *
     * @since BlackBerry 10.0.0
     */
    PpsAttributeFlag::Types flags() const;

    /*!
     * @brief Checks whether this PPS attribute is type @c Number.
     *
     * @return @c true if @c type() is @c Number, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isNumber() const;

    /*!
     * @brief Checks whether this PPS attribute is type @c bb::PpsAttribute::Bool.
     *
     * @return @c true if @c type() is @c bb::PpsAttribute::Bool, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isBool() const;

    /*!
     * @brief Checks whether this PPS attribute is type @c bb::PpsAttribute::String.
     *
     * @return @c true if @c type() is @c bb::PpsAttribute::String, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isString() const;

    /*!
     * @brief Checks whether this PPS attribute is type @c bb::PpsAttribute::Array.
     *
     * @return @c true if @c type() is @c bb::PpsAttribute::Array, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isArray() const;

    /*!
     * @brief Checks whether this PPS attribute is type @c bb::PpsAttribute::Object.
     *
     * @return @c true if @c type() is @c bb::PpsAttribute::Object, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isObject() const;

    /*!
     * @brief Gets the value of this attribute as a @c double.
     *
     * @details If @c type() is @c bb::PpsAttribute::Number, then this will return the number value as a @c double.
     *
     * If @c type() is @c bb::PpsAttribute::Bool or @c bb::PpsAttribute::String, this will convert the raw value to a @c double using
     * @c QVariant.toDouble().
     *
     * @return The value of the PPS attribute as a @c double if the value can be represented as a
     * @c double, 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    double toDouble() const;

    /*!
     * @brief Gets the value of this attribute as a @c qlonglong.
     *
     * @details If @c type() is @c bb::PpsAttribute::Number, then this will return the number value as a @c qlonglong.
     * 
     * If @c type() is @c bb::PpsAttribute::Bool or @c bb::PpsAttribute::String, this will convert the raw value to a @c qlonglong using
     * @c QVariant.toLongLong().
     *
     * @return The value of the PPS attribute as a @c qlongong if the value can be represented as a
     * @c qlongong, 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    qlonglong toLongLong() const;

    /*!
     * @brief Gets the value of this attribute as an @c int.
     *
     * @details If @c type() is @c bb::PpsAttribute::Number, then this will return the number value as an @c int.
     * 
     * If @c type() is @c bb::PpsAttribute::Bool or @c bb::PpsAttribute::String, this will convert the raw value to an @c int using
     * @c QVariant.toInt().
     *
     * @return The value of the PPS attribute as an @c int if the value can be represented as an
     * @c int, 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    int toInt() const;

    /*!
     * @brief Gets the value of this attribute as a @c bool.
     *
     * @details If @c type() is @c bb::PpsAttribute::Bool, then this will return the Boolean value as a @c bool.
     *
     * If @c type() is @c bb::PpsAttribute::Number or @c bb::PpsAttribute::String, this will convert the raw value to a @c bool using
     * @c QVariant.toBool().
     *
     * @return The value of the PPS attribute as a @c bool if the value can be represented as a
     * @c bool, false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool toBool() const;

    /*!
     * @brief Gets the value of this attribute as a @c QString.
     *
     * @details If @c type() is @c bb::PpsAttribute::String, then this will return the string value as a @c QString.
     *
     * If @c type() is @c bb::PpsAttribute::Bool or @c bb::PpsAttribute::Number, this will convert the raw value to a @c QString using
     * @c QVariant.toString().
     *
     * @return The value of the PPS attribute as a @c QString if the value can be represented as
     * a @c QString, a default-constructed @c QString otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QString toString() const;

    /*!
     * @brief Gets the value of this attribute as a @c QList.
     *
     * @return The value of the PPS attribute as a @c QList if @c type() is @c bb::PpsAttribute::Array, a
     * default-constructed @c QList<PpsAttribute> otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QList<PpsAttribute> toList() const;

    /*!
     * @brief Gets the value of this attribute as a @c QMap.
     *
     * @return The value of the PPS attribute as a @c QMap if @c type() is @c bb::PpsAttribute::Object, a
     * default-constructed @c QMap<QString, PpsAttribute> otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, PpsAttribute> toMap() const;

    /*!
     * @brief Gets the value of this attribute as a @c QVariant.
     *
     * @return The value of the PPS attribute as a @c QVariant.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant toVariant() const;

private:
//!@cond PRIVATE
    QSharedDataPointer<PpsAttributePrivate> d;
    friend class PpsAttributePrivate;
//!@endcond
};

/*!
 * @brief Streams debug output about the PPS attribute to the QDebug stream object.
 *
 * @param dbg         The QDebug stream.
 * @param attribute   The attribute to output debug information about.
 * @return            The QDebug stream.
 *
 * @since BlackBerry 10.0.0
 */
BB_CORE_EXPORT QDebug operator<<(QDebug dbg, const PpsAttribute &attribute);

} // namespace bb

#endif // BB_CORE_PPSOBJECT_HPP
