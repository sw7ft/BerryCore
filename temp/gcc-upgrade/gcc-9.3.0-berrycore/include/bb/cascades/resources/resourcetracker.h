/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_resourcetracker_h
#define cascades_resourcetracker_h

#include <bb/cascades/bbcascades_global.h>
#include <QtCore/QObject>

#include <bb/cascades/BaseObject>
#include "bb/cascades/resources/resourcestate.h"

namespace bb {
namespace cascades {

class ResourceTrackerPrivate;
/*!
    *
    * @brief Abstract base class inherited by all resource trackers.
    *
    * A resource tracker is used to access the asynchronous features of resources, such as the state.
    * All resources have a state that can be accessed, but some resources (for example, Image)
    * also have details about the size which can be accessed. Trackers also have signals that
    * are emitted when a state or other property is updated.
    *
    * @see ImageTracker
    *
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly
 *
 * @since BlackBerry 10.0.0
    */
class BBCASCADES_EXPORT ResourceTracker : public BaseObject {
    Q_OBJECT

    /*!
        * @brief The current state for the resource.
        *
        * Default state is Unknown.
        *
        * When the state changes, the stateChanged() signal will be emitted.
     *
     * @since BlackBerry 10.0.0
        */
    Q_PROPERTY(bb::cascades::ResourceState::Type state READ state NOTIFY stateChanged FINAL)

public:
    virtual ~ResourceTracker();

    /*!
     * @brief Returns the current resource state.
     *
     * @return Current resource state.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::ResourceState::Type state() const;

    /*!
     * @brief Determines whether the resource is in one of the error states.
     *
     * @return @c true if the image is in any error state, @c false otherwise.
     *
     * @see ResourceTracker::State
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool hasErrors() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the state is changed for this resource.
     *
     * @note Due to a work around for a Qt Core issue with accessing enums from QML,
     * the argument of this signal doesn't follow naming convention for signals in
     * which the signal arguments are typically named to match the associated property's name.
     * Use the object's property to access current property value instead of the signal
     * argument to avoid runtime errors (i.e. use @c state instead of @c newState).
     *
     * @param newState The new state.
     *
     * @since BlackBerry 10.0.0
     */
    void stateChanged(bb::cascades::ResourceState::Type newState);

protected:
    /*! @cond PRIVATE */
    ResourceTracker(ResourceTrackerPrivate* _d_ptr, QObject *parent = 0);
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(ResourceTracker)
    Q_DISABLE_COPY(ResourceTracker)
    /*! @endcond */

};
}
}

#endif // cascades_resourcetracker_h
