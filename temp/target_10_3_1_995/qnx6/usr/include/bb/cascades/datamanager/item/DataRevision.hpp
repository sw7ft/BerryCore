/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_DATAREVISION_HPP_
#define BB_CASCADES_DATAMANAGER_DATAREVISION_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/Revision>
#include <QSharedPointer>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataRevisionPrivate;

/*!
 * @headerfile DataRevision.hpp <bb/cascades/datamanager/DataRevision>
 *
 * @brief This class encapsulates revision information for some data.
 *
 * This class provides a copyable wrapper for a @c Revision pointer and owns the @c %Revision.
 *
 * This class functions much like a shared pointer on an immutable and private @c %Revision
 * object since it doesn't change the @c %Revision and deletes it when this
 * @c DataRevision goes out of scope, provided that no other @c %DataRevision objects
 * are referencing the @c %Revision.
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT DataRevision
{
public:
    /*!
     * @brief Constructs a @c DataRevision given a @c Revision.
     *
     * @note The @c %Revision is destroyed when all @c %DataRevision
     * objects that point to it go out of scope.
     *
     * @param rev A pointer to a @c %Revision to be managed. This pointer must not be null.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataRevision(Revision* rev);

    /*!
     * @brief Constructs a @c DataRevision.
     *
     * @since BlackBerry 10.2.0
     */
    DataRevision();

    /*!
     * @brief Copy constructor.
     *
     * This function constructs a @c DataRevision containing exactly the same values
     * as the provided @c %DataRevision.
     *
     * @note The internal @c Revision is shared after this copy and
     * destroyed when all @c %DataRevision objects that point to it
     * go out of scope.
     *
     * @param other The @c DataRevision object to copy.
     *
     * @since BlackBerry 10.2.0
     */
    DataRevision(const DataRevision& other);

    /*!
     * @brief Assignment operator.
     *
     * This function assigns values from the given @c DataRevision to the returned @c %DataRevision.
     *
     * @param other The @c DataRevision object to assign from.
     *
     * @return The revised @c DataRevision instance.
     *
     * @since BlackBerry 10.2.0
     */
    DataRevision& operator=(const DataRevision &other);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataRevision();

    /*!
     * @brief Update this data revision with another one.
     *
     * After the update, this revision must be greater than or equal to both
     * its previous state and @c other.
     *
     * @param other The revision to update this one with.
     *
     * @since BlackBerry 10.2.0
     */
    void update(const DataRevision &other);

    /*!
     * @brief Reset the revision to the "null" state.
     *
     * @since BlackBerry 10.2.0
     */
    void clear();

    /*!
     * @brief Compare whether this revision equals another.
     *
     * @param other The @c DataRevision object to compare with.
     *
     * @return @c True if equal, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator==(const DataRevision &other) const;

    /*!
     * @brief Compare whether this revision is greater than (newer than) another.
     *
     * @param other The @c DataRevision object to compare with.
     *
     * @return @c True if this revision is newer, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator>(const DataRevision &other) const;

    /*!
     * @brief Compare whether this revision is not equal to another.
     *
     * @param other The @c DataRevision object to compare with.
     *
     * @return @c True if not equal, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator!=(const DataRevision &other) const;

    /*!
     * @brief Compare whether this revision is less than (older than) another.
     *
     * @param other The @c DataRevision object to compare with.
     *
     * @return @c Tue if this revision is older, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator<(const DataRevision &other) const;

    /*!
     * @brief Compare whether this revision is less than or equal to (older than or equal to) another.
     *
     * @param other The @c DataRevision object to compare with.
     *
     * @return @c True if this revision is older or same age, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator<=(const DataRevision &other) const;

    /*!
     * @brief Compare whether this revision is greater than or equal to (newer than or equal to) the other.
     *
     * @param other The @c DataRevision object to compare with.
     *
     * @return @c True if this revision is newer or same age, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator>=(const DataRevision &other) const;

    /*!
     * @brief Check whether this revision object contains any revision information.
     *
     * Objects created with the default constructor will initially return @c true
     * for this method.
     *
     * @return @c True if the data revision contains no revision information, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isNull() const;

    /*!
     * @brief Convert this revision to a string representation.
     *
     * @return The string representation.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

private:
    /*! @cond PRIVATE */
    QSharedPointer<Revision> m_revision;
    /*! @endcond */
};

QDebug operator<<(QDebug dbg, const DataRevision &revision);

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_DATAREVISION_HPP_ */
