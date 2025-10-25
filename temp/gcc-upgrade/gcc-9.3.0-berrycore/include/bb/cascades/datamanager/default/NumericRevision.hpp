/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_NUMERICREVISION_HPP
#define BB_CASCADES_DATAMANAGER_NUMERICREVISION_HPP

#include <QtGlobal>
#include <QDebug>
#include <bb/cascades/datamanager/Revision>

namespace bb
{
namespace cascades
{
namespace datamanager
{

/*!
 * @headerfile NumericRevision.hpp <bb/cascades/datamanager/NumericRevision>
 *
 * @brief A @c Revision which uses a 64-bit unsigned integer as the revision.
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT NumericRevision : public Revision
{
public:
    /*!
     * @brief Constructs a @c NumericRevision.
     *
     * The revision number will be zero.
     *
     * @since BlackBerry 10.2.0
     */
    NumericRevision ();

    /*!
     * @brief Constructs a @c NumericRevision given a revision number.
     *
     * @param revision The numeric revision number as a 64-bit unsigned integer.
     *
     * @since BlackBerry 10.2.0
     */
    explicit NumericRevision(quint64 revision);

    /*!
     * @brief Copy constructor.
     *
     * This function constructs a @c NumericRevision containing exactly the same values
     * as the provided @c %NumericRevision.
     *
     * @param other The @c NumericRevision object to copy data from.
     *
     * @since BlackBerry 10.2.0
     */
    NumericRevision(const NumericRevision& other);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~NumericRevision();

    /*!
     * @brief Check for equality.
     *
     * @param other The revision to compare against.
     *
     * @return @c True if the revisions are equal, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool equals(const Revision &other) const;

    /*!
     * @brief Check whether this revision is greater (newer) than the other.
     *
     * @param other The revision to compare against.
     *
     * @return @c True if this object is greater (newer) than the given object,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool greaterThan(const Revision &other) const;

    /*!
     * @brief Return a new revision based on this revision and another revision.
     *
     * The revision that is returned should be greater than or equal to both
     * this revision object, and @c other.
     *
     * @param other Another revision provider.
     *
     * @return A pointer to the newly created @c Revision object.
     *
     * @since BlackBerry 10.2.0
     */
    Revision* newRevision(const Revision &other) const;

    /*!
     * @brief Convert this revision to a string representation for debugging.
     *
     * @return The string representation.
     *
     * @since BlackBerry 10.2.0
     */
    QString toString() const;
};

QDebug operator<<(QDebug dbg, const NumericRevision &item);

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_NUMERICREVISION_HPP */
