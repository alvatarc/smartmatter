/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2010 The Voreen Team. <http://www.voreen.org>   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

#ifndef VRN_BINARYIMAGEPROCESSOR_H
#define VRN_BINARYIMAGEPROCESSOR_H

#include "voreen/core/processors/imageprocessordepth.h"
#include "voreen/core/ports/allports.h"

#include "voreen/core/properties/shaderproperty.h"

namespace voreen {

class BinaryImageProcessor : public ImageProcessorDepth {
public:
    BinaryImageProcessor();
    virtual Processor* create() const;

    virtual std::string getCategory() const { return "Image Processing"; }
    virtual std::string getClassName() const { return "BinaryImageProcessor"; }
    virtual CodeState getCodeState() const { return CODE_STATE_STABLE; }
    virtual std::string getProcessorInfo() const;

protected:
    void process();
    virtual void initialize() throw (VoreenException);

    virtual void loadShader();
    virtual void compileShader();

    ShaderProperty shader_;  ///< the property that controls the used shader

    RenderPort inport0_;
    RenderPort inport1_;
    RenderPort outport_;

    static const std::string shadeTexUnit0_;
    static const std::string depthTexUnit0_;
    static const std::string shadeTexUnit1_;
    static const std::string depthTexUnit1_;
};


} // namespace voreen

#endif //VRN_BINARYIMAGEPROCESSOR_H
