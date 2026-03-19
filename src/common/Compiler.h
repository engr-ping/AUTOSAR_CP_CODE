/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2023 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Compiler.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This file provides the AUTOSAR compiler abstraction for the TriCore Tasking compiler
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-01  Jk                    Initial creation
 *  01.01.00  2007-11-06  Om                    Adaptation for Tasking compiler for Infineon Tricore
 *  01.01.01  2007-11-27  Jk                    Version defines for CFG management added
 *  02.00.00  2008-04-11  Jk                    Addapted to AUTOSAR 3.0
 *  02.00.01  2008-12-09  Bir                   Correct order of pointerclass and memclass
 *  02.00.02  2009-02-09  Bir                   Correct const position in "CONSTP2*"
 *  02.00.03  2009-04-24  Bir                   Correct version define naming
 *  02.00.04  2009-09-29  Bir                   Name of version define
 *  02.01.00  2011-09-20  Bir                   Update to new template include AUTOSAR VERSION 4 and 3.2
 *  02.01.01  2014-03-20  Bir     ESCAN00074429 Rename compiler define
 *  02.01.02  2014-09-23  Bir     ESCAN00078425 Version Define with wrong Value
 *                                ESCAN00078541 _TASKING_C_TRICORE_ can be overwritten
 *  02.02.00  2017-04-05  Rna     ESCAN00094656 AR4-569: CONSTP2FUNC  macro  is  missed  in Compiler Abstraction
 *  02.03.00  2020-11-18  Bwa                   Removed AUTHOR IDENTITY, changed filter mechanism (Product instead of
 *                                              AutosarVersion)
 *  02.03.01  2021-08-24  visto   HALBE-5213    Conditional inline define
 *  02.03.02  2021-08-30  visto                 correction of compiler define
 *  02.04.00  2023-07-17  virrlu  HALBE-10052   Update to AUTOSAR Release 21-11
 *********************************************************************************************************************/

#ifndef COMPILER_H
#define COMPILER_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Compiler_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ##V_CFG_MANAGEMENT ##CQProject : CommonAsr_Tricore CQComponent : Impl_CompAbstract_Diab */
#define COMMONASR_TRICORE_IMPL_COMPABSTRACT_VERSION 0x0204
#define COMMONASR_TRICORE_IMPL_COMPABSTRACT_RELEASE_VERSION 0x00

#define COMPILER_VENDOR_ID    30u              /* Vendor ID of Vector */
#define COMPILER_MODULE_ID    198u             /* 198 is the ID of compiler abstraction */
 
/* AUTOSAR Software Specification Release Version Information */
/*            AUTOSAR Release 21-11                           */
#define COMPILER_AR_RELEASE_MAJOR_VERSION       (4u)
#define COMPILER_AR_RELEASE_MINOR_VERSION       (7u)
#define COMPILER_AR_RELEASE_REVISION_VERSION    (0u)

/* Component Version Information */
#define COMPILER_SW_MAJOR_VERSION       (2u)
#define COMPILER_SW_MINOR_VERSION       (4u)
#define COMPILER_SW_PATCH_VERSION       (0u)

#ifndef _TASKING_C_TRICORE_
# define _TASKING_C_TRICORE_
#endif

/* AUTOMATIC used for the declaration of local pointers */
#define AUTOMATIC

/* TYPEDEF shall be used within type definitions, where no memory qualifier can be specified.*/
#define TYPEDEF

/* NULL_PTR define with a void pointer to zero definition*/
#ifndef NULL_PTR
  #define NULL_PTR  ((void *)0)
#endif

/* INLINE  define for abstraction of the keyword inline*/
#ifndef INLINE
#define INLINE     inline
#endif

/* LOCAL_INLINE define for abstraction of the keyword inline in functions with "static" scope.
   Different compilers may require a different sequence of the keywords "static" and "inline"
   if this is supported at all. */
#ifndef LOCAL_INLINE
#define LOCAL_INLINE    static inline
#endif

/* FUNC macro for the declaration and definition of functions, that ensures correct syntax of function declarations
   rettype     return type of the function
   memclass    classification of the function itself*/
#define FUNC(rettype, memclass) rettype memclass /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* FUNC_P2CONST macro for declaration and definition of functions returning a pointer to a constant, that ensures 
     correct syntax of function declarations.
   rettype     return type of the function
   ptrclass    defines the classification of the pointer distance
   memclass    classification of the function itself*/
#define FUNC_P2CONST(rettype, ptrclass, memclass) const rettype ptrclass * memclass /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* FUNC_P2VAR macro for the declaration and definition of functions returning a pointer to a variable, that ensures
     correct syntax of function declarations
   rettype     return type of the function
   ptrclass    defines the classification of the pointer distance
   memclass    classification of the function itself*/
#define FUNC_P2VAR(rettype, ptrclass, memclass) rettype ptrclass * memclass /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* P2VAR macro for the declaration and definition of pointers in RAM, pointing to variables
   ptrtype     type of the referenced variable memory class
   memclass    classification of the pointer variable itself
   ptrclass    defines the classification of the pointer distance
 */
#define P2VAR(ptrtype, memclass, ptrclass) memclass ptrtype ptrclass * /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* P2CONST macro for the declaration and definition of pointers in RAM pointing to constants
   ptrtype     type of the referenced data
   memclass    classification of the pointer variable itself
   ptrclass    defines the classification of the pointer distance
 */
#define P2CONST(ptrtype, memclass, ptrclass) const memclass ptrtype ptrclass * /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* CONSTP2VAR macro for the declaration and definition of constant pointers accessing variables
   ptrtype     type of the referenced data
   memclass    classification of the pointer variable itself
   ptrclass    defines the classification of the pointer distance
 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass) memclass ptrtype ptrclass * const /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* CONSTP2CONST macro for the declaration and definition of constant pointers accessing constants
   ptrtype     type of the referenced data
   memclass    classification of the pointer variable itself
   ptrclass    defines the classification of the pointer distance
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const memclass ptrtype ptrclass * const /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* P2FUNC macro for the type definition of pointers to functions
   rettype     return type of the function
   ptrclass    defines the classification of the pointer distance
   fctname     function name respectively name of the defined type
 */
#define P2FUNC(rettype, ptrclass, fctname) rettype (ptrclass * fctname) /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* CONSTP2FUNC macro for the type definition of pointers to functions
   rettype     return type of the function
   ptrclass    defines the classification of the pointer distance
   fctname     function name respectively name of the defined type
 */
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (ptrclass * const fctname) /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* CONST macro for the declaration and definition of constants
   type        type of the constant
   memclass    classification of the constant itself
 */
#define CONST(type, memclass) const type memclass /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/* VAR macro for the declaration and definition of variables
   vartype     type of the variable
   memclass    classification of the variable itself
 */
#define VAR(vartype, memclass) vartype memclass /* PRQA S 3410 */ /* MD_Compiler_19.10 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/****************************************************************************/
/*  MISRA deviations                                                        */
/****************************************************************************/
/* Justification for module-specific MISRA deviations:
MD_Compiler_19.10:
  Reason: Macro used in structures, which depend on used compiler and which do not allow brackets e.g. declaration of functions and variables.
  Risk: None atomic parameter lead to compile errors.
  Prevention: Used parameter is always atomic.
*/
#endif /* COMPILER_H */

/**********************************************************************************************************************
 *  END OF FILE: Compiler.h
 *********************************************************************************************************************/
