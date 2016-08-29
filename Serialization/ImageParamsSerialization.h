/* ***** BEGIN LICENSE BLOCK *****
 * This file is part of Natron <http://www.natron.fr/>,
 * Copyright (C) 2016 INRIA and Alexandre Gauthier-Foichat
 *
 * Natron is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Natron is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Natron.  If not, see <http://www.gnu.org/licenses/gpl-2.0.html>
 * ***** END LICENSE BLOCK ***** */

#ifndef IMAGEPARAMSSERIALIZATION_H
#define IMAGEPARAMSSERIALIZATION_H

#include "Serialization/NonKeyParamsSerialization.h"
#include "Serialization/RectDSerialization.h"

#ifdef NATRON_BOOST_SERIALIZATION_COMPAT
#include "Engine/ImageComponents.h"
#endif

SERIALIZATION_NAMESPACE_ENTER;

class ImageComponentsSerialization
: public SerializationObjectBase
{
public:

    ImageComponentsSerialization()
    : SerializationObjectBase()
    {

    }

    virtual ~ImageComponentsSerialization()
    {

    }

    // The layer name, e.g: Beauty
    std::string layerName;

    // The components global label, e.g: "RGBA" or "MotionPass"
    // If not provided, this is just the concatenation of all channel names
    std::string globalCompsName;

    // Each individual channel names, e.g: "R", "G", "B", "A"
    std::vector<std::string> channelNames;

    virtual void encode(YAML::Emitter& em) const OVERRIDE;

    virtual void decode(const YAML::Node& node) OVERRIDE;

};

class ImageParamsSerialization
: public NonKeyParamsSerialization
{
public:

    RectDSerialization rod;
    bool isRoDProjectFormat;
    double par;
    ImageComponentsSerialization components;
    int bitdepth;
    int fielding;
    int premult;
    unsigned int mipMapLevel;


    ImageParamsSerialization()
    : NonKeyParamsSerialization()
    {

    }

    virtual ~ImageParamsSerialization()
    {

    }

    virtual void encode(YAML::Emitter& em) const OVERRIDE;

    virtual void decode(const YAML::Node& node) OVERRIDE;
};

SERIALIZATION_NAMESPACE_EXIT

#ifdef NATRON_BOOST_SERIALIZATION_COMPAT
/**
 * @brief Deprecated, just used for backward compatibility in NodeSerialization
 **/
template<class Archive>
void
NATRON_NAMESPACE::ImageComponents::serialize(Archive & ar,
                           const unsigned int /*version*/)
{
    ar &  boost::serialization::make_nvp("Layer", _layerName);
    ar &  boost::serialization::make_nvp("Components", _componentNames);
    ar &  boost::serialization::make_nvp("CompName", _globalComponentsName);
}
#endif


#endif // IMAGEPARAMSSERIALIZATION_H
