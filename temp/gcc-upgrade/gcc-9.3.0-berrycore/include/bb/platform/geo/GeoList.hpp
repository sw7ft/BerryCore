/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEO_LIST_HPP
#define BB_PLATFORM_GEO_GEO_LIST_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/BoundingBox>
#include <bb/platform/geo/Geographic>

#include <QStringList>
#include <QSharedDataPointer>
#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{
class GeoListPrivate;

/**
 * @headerfile GeoList.hpp <bb/platform/geo/GeoList>
 *
 * @brief A container of @c Geographic elements.
 *
 * @details Each element's ID must be unique. The element's ID is used as a
 * handle for the element. You can retrieve each element's ID using
 * <code>Geographic.getId()</code>.
 *
 * Object Ownership
 * -----------------
 * The @c Geographic elements in this list are not owned by this
 * list. When this @c GeoList is deleted, the elements contained
 * in it still exist. @c Geographic elements are usually owned by the
 * client application, or by the @c MapData or @c DataProvider objects used
 * with @c MapView.
 *
 * Reference Type
 * --------------
 * @c GeoList is expected to be used as a <a
 * href="http://en.wikipedia.org/wiki/Value_type">value type</a>.
 * However, GeoList is a collection of raw pointers to instances of <a
 * href="http://en.wikipedia.org/wiki/Reference_type">reference type</a>.
 * As such, care needs to be made when referencing this object's contents
 * in multithreaded environments. For example, deletion in one thread can
 * cause a dangling pointer in another thread.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_GEO_EXPORT GeoList
{

public:
    /** @brief Constructor
     *
     * @since BlackBerry 10.0.0
     */
    GeoList();

    /** @brief Copy Constructor
     *
     * @since BlackBerry 10.0.0
     */
    GeoList( GeoList const& src );

    /** @brief Destructor
     *
     * @since BlackBerry 10.0.0
     */
    ~GeoList();

    /** @brief Assignment Operator
     *
     * @since BlackBerry 10.0.0
     */
    GeoList& operator=( const GeoList& src );

    /**
     * @brief Gets the bounding box that contains all the elements in this
     * list.
     * The borders of the bounding box include all the geographic elements
     * in this list.
     * @return The bounding box surrounding this list of geographic
     * elements.
     *
     * @since BlackBerry 10.0.0
     */
    BoundingBox boundingBox() const;

    /**
     * @brief Adds a @c Geographic element to this list.
     *
     * @since BlackBerry 10.0.0
     */
    bool add( Geographic* element );

    /**
     * @brief Copies all @c Geographic elements in the @c GeoList given as
     * the parameter to this list.
     *
     * @param list The list to copy from.
     *
     * @since BlackBerry 10.0.0
     */
    void add( const GeoList& list );

    /**
     * @brief Gets all the @c Geographic elements within the given bounding
     * box from this list.
     *
     * @since BlackBerry 10.0.0
     */
    GeoList find( const BoundingBox& boundingBox ) const;

    /**
     * @brief Gets the @c Geographic element with the given ID from this
     * list.
     *
     * @return NULL if the element was not found.
     *
     * @since BlackBerry 10.0.0
     */
    Geographic* geographic( const QString& id ) const;

    /**
     * @brief Gets all the @c Geographic elements with the given IDs from
     * this list.
     *
     * @since BlackBerry 10.0.0
     */
    GeoList find( const QStringList& ids ) const;

    /**
     * @brief Removes the @c Geographic element with the given ID from this
     * list.
     *
     * Note: This does not free the memory pointed to by
     * this pointer.
     *
     * @return @c true if the element existed and was removed;
     * otherwise, returns @c false.
     *
     * @since BlackBerry 10.0.0
     */
    bool remove( const QString& id );

    /**
     * @brief Removes all @c Geographic elements from this list.
     *
     * @return @c true if any changes occurred.
     *
     * @since BlackBerry 10.0.0
     */
    bool clear();

    /**
     * @brief Retrieves a list of all the IDs within this list.
     *
     * @return A collection of @c QString ids.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList ids() const;

    /**
     * @brief Retrieves a list of all the @c Geographic elements within
     * this list.
     *
     * @return A collection of @c Geographic objects.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Geographic*> toQList() const;

    /**
     * @brief Determines if this list has any @c Geographic elements in it.
     *
     * @return @c true if the number of @c Geographic elements in
     * this list is zero, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isEmpty() const;

    /**
     * @brief Retrieves the number of @c Geographic elements in this
     * list.
     *
     * @return The number of @c Geographic elements in this list.
     *
     * @since BlackBerry 10.0.0
     */
    int count() const;

private:
    QSharedDataPointer<GeoListPrivate> p;

};

BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const GeoList& pt );


} // namespace geo
} // namespace platform
} // namespace bb
#endif // BB_PLATFORM_GEO_GEO_LIST_HPP
