/**********************************************************************
 *                                                                    *
 * tgt - Tiny Graphics Toolbox                                        *
 *                                                                    *
 * Copyright (C) 2006-2008 Visualization and Computer Graphics Group, *
 * Department of Computer Science, University of Muenster, Germany.   *
 * <http://viscg.uni-muenster.de>                                     *
 *                                                                    *
 * This file is part of the tgt library. This library is free         *
 * software; you can redistribute it and/or modify it under the terms *
 * of the GNU Lesser General Public License version 2.1 as published  *
 * by the Free Software Foundation.                                   *
 *                                                                    *
 * This library is distributed in the hope that it will be useful,    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU Lesser General Public License for more details.                *
 *                                                                    *
 * You should have received a copy of the GNU Lesser General Public   *
 * License in the file "LICENSE.txt" along with this library.         *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 **********************************************************************/

#ifndef TGT_FRUSTUM_H
#define TGT_FRUSTUM_H

#include "tgt/config.h"
#include "tgt/types.h"
#include "tgt/vector.h"
#include "tgt/bounds.h"
#include "tgt/math.h"

namespace tgt {

// foreward declaration
class Camera;

/**
 * This class is used by the Camera for culling in connection with axis aligned bounding boxes
 * or points.
 */
class Frustum {
    
private:
    /// the distances from the center of the near plane to the left, right, top and bottom borders
    float lnear_;
    float rnear_;
    float bnear_;
    float tnear_;
    /// the distances from the position of the camera to the near- and far-plane
    float nearDist_;
    float farDist_;
    
    enum normalsEnum { LEFTN, RIGHTN, TOPN, BOTTOMN, NEARN, FARN, NORMALS_NUM };
    
    vec3 normals_[NORMALS_NUM];

    /// Points on the 6 planes; the position campos_ of the Camera lies on
    /// the top, bottom, left and right planes so we need only this point for the four
    /// These are used in culling methods.
    vec3 nearp_;
    vec3 farp_;
    vec3 campos_;


public:

    /** Constructor
     *
     * @param fovy the viewing angle in vertical direction in degrees.
     */
    Frustum(float fovy, float ratio, float nearDist, float farDist);
    Frustum(float left, float right, float bottom, float top, float nearDist, float farDist);

    /// These methodes can be used to find out wether or not a bounding-box or a point are visible.
    /// Do not forget to update() before useage if camera position or viewing axis changed!
    bool isCulledXZ(const Bounds& b) const;
    bool isCulled(const Bounds& b) const;
    bool isCulled(const vec3& v) const;

    /// update normals and points on 6 planes to fit to current frustem parameters and to
    /// parameters of the camera given
    void update(Camera* c);

    /**
     * Returns the viewing angle in vertical direction in degrees.
     */
    float getFovy() const {
        return rad2deg(atanf(tnear_/nearDist_) - atanf(bnear_/nearDist_) );
    }
    
    float getRatio() const {
        return (rnear_ - lnear_)/(tnear_ - bnear_);
    }
    
    float getNearDist() const  {
        return nearDist_;
    }
    
    float getFarDist() const {
        return farDist_;
    }

    float getLeft() const {
        return lnear_;
    }
    float getRight() const {
        return rnear_;
    }
    float getTop() const {
        return tnear_;
    }
    float getBottom() const {
        return bnear_;
    }

    /// set the viewing angle in vertical direction in degrees.
    void setFovy(float fovy) {
        float halfheight = tanf(0.5f * deg2rad(fovy)) * nearDist_;
        tnear_ =  halfheight;
        bnear_ = -halfheight;
    }
    /// set width of frustum according to current height (or y viewing angle)
    void setRatio(float ratio) {
        float halfwidth = 0.5f * (tnear_-bnear_) * ratio;
        lnear_ = -halfwidth;
        rnear_ =  halfwidth;
		bnear_ = -halfwidth / ratio;
        tnear_ =  halfwidth / ratio;		
    }
    void setNearDist(float nearDist) {
        nearDist_ = nearDist;
    }
    void setFarDist(float farDist) {
        farDist_ = farDist;
    }

    void setLeft(float v) {
        lnear_ = v;
    }
    void setRight(float v) {
        rnear_ = v;
    }
    void setTop(float v) {
        tnear_ = v;
    }
    void setBottom(float v) {
        bnear_ = v;
    }

    const vec3& leftn() const {
        return normals_[LEFTN];
    }

    const vec3& rightn() const {
        return normals_[RIGHTN];
    }

    const vec3& bottomn() const {
        return normals_[BOTTOMN];
    }

    const vec3& topn() const {
        return normals_[TOPN];
    }

    const vec3& nearn() const {
        return normals_[NEARN];
    }

    const vec3& farn() const {
        return normals_[FARN];
    }

    const vec3& nearp() const {
        return nearp_;
    }

    const vec3& farp() const {
        return farp_;
    }

    const vec3& campos() const {
        return campos_;
    }

    /// Get the 1 of the 6 normals leftn, rightn, bottomn, topn, nearn, farn specified by the
    /// number num.
    /// 
    /// Can be used to handle normals within a for-loop e.g. when culling against frustum, see
    /// tgt::Camara::isCulled, tgt::Camera::isCulledXZ.
    const vec3& getNormal(int num) const {
        return normals_[num];
    }
};

}

#endif //TGT_FRUSTUM_H_
