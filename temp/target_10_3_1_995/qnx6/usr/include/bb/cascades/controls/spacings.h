/* Copyright (C) 2011 Research In Motion Limited.  */

#ifndef cascades_spacings_h
#define cascades_spacings_h

#include <QtDeclarative/QtDeclarative>
#include <QObject>
#include <QScopedPointer>
#include <QVariant>

#include "bb/cascades/bbcascades_global.h"
#include <bb/cascades/core/uiobject.h>

namespace bb {
  namespace cascades {
       
    class ControlPrivate;
    class SpacingsPrivate;
    
    /*!
     * @brief A description of the white space allocated adjacent to the border of a component, inside or outside.
     *
     * @since BlackBerry 10.2.0
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     */
    class BBCASCADES_EXPORT Spacings : public BaseObject {
      Q_OBJECT    
      
      /*!
       * @brief The left offset for the Spacings group.
       *
       * This is the space specified to the compent adjacent to its left boundary, the default is not defined, i.e. @c NaN.
       */
      Q_PROPERTY(float leftOffset   READ leftOffset   WRITE setLeftOffset 	RESET resetLeftOffset   NOTIFY leftOffsetChanged    FINAL)
      /*!
       * @brief The right offset for the Spacings group.
       *
       * This is the space specified to the compent adjacent to its right boundary, the default is not defined, i.e. @c NaN.
       */
      Q_PROPERTY(float rightOffset  READ rightOffset  WRITE setRightOffset  RESET resetRightOffset  NOTIFY rightOffsetChanged   FINAL)
      /*!
       * @brief The top offset for the Spacings group.
       *
       * This is the space specified to the compent adjacent to its top boundary, the default is not defined, i.e. @c NaN.
       */
      Q_PROPERTY(float topOffset    READ topOffset    WRITE setTopOffset    RESET resetTopOffset    NOTIFY topOffsetChanged     FINAL)
      /*!
       * @brief The bottom offset for the Spacings group.
       *
       * This is the space specified to the compent adjacent to its bottom boundary, the default is not defined, i.e. @c NaN.
       */
      Q_PROPERTY(float bottomOffset READ bottomOffset WRITE setBottomOffset RESET resetBottomOffset NOTIFY bottomOffsetChanged  FINAL)
     
      
      
    public:

      Spacings();
      Spacings(ControlPrivate* pcv);  
      virtual ~Spacings();
    
      
      /********** Left Offset ************/
      /*!
       * @brief Returns the left offset.
       *
       * @return The left offset.
       */
      float leftOffset();
      /*!
       * @brief Sets the left offset.
       *
       * After the offset is set, the @c leftOffsetChanged( float ) signal is emitted.
       *
       * @param fOffset The new left.
       */
      Q_SLOT void setLeftOffset(float fOffset);      
      /*!
       * @brief Resets the @c #leftOffset to its default value.
       */
      Q_SLOT void resetLeftOffset();
      

      /********** Right Offset ************/
      /*!
       * @brief Returns the right offset.
       *
       * @return The right offset.
       */
      float rightOffset();
      /*!
       * @brief Sets the right offset.
       *
       * After the offset is set, the @c rightOffsetChanged() signal is emitted.
       *
       * @param fOffset The new right.
       */            
      Q_SLOT void setRightOffset(float fOffset);
      /*!
       * @brief Resets the @c #rightOffset to its default value.
       */
      Q_SLOT void resetRightOffset();
      
       
      /********** Top Offset ************/
      /*!
       * @brief Returns the top offset.
       *
       * @return The top offset.
       */
      float topOffset();
      /*!
       * @brief Sets the top offset.
       *
       * After the offset is set, the @c topOffsetChanged( float ) signal is emitted.
       *
       * @param fOffset The new value.
       */            
      Q_SLOT void setTopOffset(float fOffset);   
      /*!
       * @brief Resets the @c #topOffset to its default value.
       */
      Q_SLOT void resetTopOffset();
      
  
      /********** Bottom Offset ************/
      /*!
       * @brief Returns the bottom offset.
       *
       * @return The bottom offset.
       */
      float bottomOffset();
      /*!
       * @brief Sets the bottom offset for the control.
       *
       * After the is offset is changed, the @c bottomOffsetChanged( float ) signal is emitted.
       *
       * @param fOffset The new value.
       */            
      Q_SLOT void setBottomOffset(float fOffset);   
      /*!
       * @brief Resets the @c #bottomOffset to its default value.
       */
      Q_SLOT void resetBottomOffset();
      
    Q_SIGNALS:

      /*!
       * @brief Emitted when the @c #leftOffset property changes.
       *
       * @param fOffset The new left offset.
       */
      void leftOffsetChanged(float fOffset);
      
      /*!
       * @brief Emitted when the @c #rightOffset property changes.
       *
       * @param fOffset The new right offset.
       */      
      void rightOffsetChanged(float fOffset);
      
      /*!
       * @brief Emitted when the @c #topOffset property changes.
       *
       * @param fOffset The new top offset.
       */      
      void topOffsetChanged(float fOffset);
      
      /*!
       * @brief Emitted when the @c #bottomOffset property changes.
       *
       * @param fOffset The new bottom offset.
       */      
      void bottomOffsetChanged(float fOffset);
    
    private:      
      friend class ControlPrivate;

      /*!
       * @brief The private representation of the Object.
       */
      Q_DECLARE_PRIVATE(Spacings)
      Q_DISABLE_COPY(Spacings)
    
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::Spacings)
#endif
