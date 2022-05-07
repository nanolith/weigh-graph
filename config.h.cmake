/**
 * \file weightgraph/config.h
 *
 * \brief Generated configuration file data for weightgraph.
 *
 * \copyright 2022 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#define MAKE_C_VERSION(X,Y) V ## X ## _ ## Y
#define WEIGHTGRAPH_VERSION_SYM \
    MAKE_C_VERSION(@WEIGHTGRAPH_VERSION_MAJOR, @WEIGHTGRAPH_VERSION_MINOR)

#define WEIGHTGRAPH_VERSION_STRING \
    "@WEIGHTGRAPH_VERSION_MAJOR.@WEIGHTGRAPH_VERSION_MINOR.@WEIGHTGRAPH_VERSION_REL"
