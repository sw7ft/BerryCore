/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
//! @cond PRIVATE
#ifndef BB_SYSTEM_CONTEXTCLASSIFICATION_HPP
#define BB_SYSTEM_CONTEXTCLASSIFICATION_HPP

#include <bb/system/Global>

#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile ContextClassification.hpp <bb/system/ContextClassification>
 *
 * @brief Classifications of data collected by the Context Collection Library.
 *
 * The classification is used to indicate Personally Identifying
 * Information (PII), which is hashed before being sent to RIM.
 *
 * @xmlonly
 * <apigrouping group="Platform/Context collector"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 */
class BB_SYSTEM_EXPORT ContextClassification
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief Classifications of data collected by the Context Collection Library.
     *
     * The classification is used to indicate Personally Identifying
     * Information (PII), which is hashed before being sent to RIM.
     */
    enum Type { 

        /*!
         * @brief Public information.
         * @details The information does not identify a specific user and is not hashed.
         */
        Public = 0, 
        
        /*!
         * @brief Private information that is hashed with a standard hashing algorithm.
         * @details The information identifies a specific user and is hashed with a standard obfuscation algorithm.
         */
        Private = 1,
        
        /*!
         * @brief Private information that is hashed with a custom algorithm.
         * @details The information identifies a specific user and is hashed with an algorithm designed for
         * short strings. Information such as a user's PIN may be classified this way.
         */
        PrivateShort = 2
    };

private:
    //! @cond PRIVATE
    ContextClassification();
    ~ContextClassification();
    //! @endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::ContextClassification)
#endif // BB_SYSTEM_CONTEXTCLASSIFICATION_HPP
//! @endcond
