/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkLayer_h
#define SkLayer_h

#include "SkCanvas.h"
#include "SkRefCnt.h"
#include "SkTDArray.h"
#include "SkColor.h"
#include "SkPoint.h"
#include "SkSize.h"

class SkPicture;


struct SkLength {
  enum SkLengthType { Undefined, Auto, Relative, Percent, Fixed, Static, Intrinsic, MinIntrinsic };
  SkLengthType type;
  SkScalar value;
  SkLength() {
    type = Undefined;
    value = 0;
  }
  bool defined() {
    if (type == Undefined)
      return false;
    return true;
  }
  float calcFloatValue(float max) const {
    switch (type) {
      case Percent:
        return (max * value) / 100.0f;
      case Fixed:
        return value;
      default:
        return value;
    }
  }
};

class SkLayer /*: public SkRefCnt*/ {

public:
    SkLayer() {
      m_doRotation = false;
      m_isFixed = false;
      m_backgroundColorSet = false;
      m_angleTransform = 0;
      m_opacity = 1;
      m_size.set(0, 0);
      m_translation.set(0, 0);
      m_anchorPoint.set(0.5, 0.5);
      m_scale.set(1, 1);
    }

    SkLayer(SkLayer* layer) {
      memcpy(this, layer, sizeof(*this));
    }

    virtual ~SkLayer() {};

    // setters

    void setSize(SkScalar w, SkScalar h) { m_size.set(w, h); }
    void setOpacity(SkScalar opacity) { m_opacity = opacity; }
    void setTranslation(SkScalar x, SkScalar y) { m_translation.set(x, y); }
    void setRotation(SkScalar a) { m_angleTransform = a; m_doRotation = true; }
    void setScale(SkScalar x, SkScalar y) { m_scale.set(x, y); }
    void setPosition(SkScalar x, SkScalar y) { m_position.set(x, y); }
    void setAnchorPoint(SkScalar x, SkScalar y) { m_anchorPoint.set(x, y); }
    virtual void setBackgroundColor(SkColor color) { m_backgroundColor = color; m_backgroundColorSet = true; }
    void setFixedPosition(SkLength left, SkLength top, SkLength right, SkLength bottom) {
      m_fixedLeft = left;
      m_fixedTop = top;
      m_fixedRight = right;
      m_fixedBottom = bottom;
      m_isFixed = true;
    }

    // getters

    SkPoint position() { return m_position; }
    SkPoint translation() { return m_translation; }
    SkSize  size() { return m_size; }

    // paint method

    virtual void paintOn(SkPoint offset, SkSize size, SkScalar scale, SkCanvas*) = 0;

    // children manipulation

//    void removeAllChildren();
//    void addChildren(LayerAndroid* layer);

public:

    bool m_doRotation;
    bool m_isFixed;
    bool m_backgroundColorSet;

    // layers properties

    SkScalar m_angleTransform;
    SkScalar m_opacity;

    SkSize m_size;
    SkPoint m_position;
    SkPoint m_translation;
    SkPoint m_anchorPoint;
    SkPoint m_scale;

    SkLength m_fixedLeft;
    SkLength m_fixedTop;
    SkLength m_fixedRight;
    SkLength m_fixedBottom;

    SkColor m_backgroundColor;

//    SkTDArray<SkLayer*> m_children;
};

#endif
