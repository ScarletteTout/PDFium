// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef FPDFSDK_PDFWINDOW_PWL_EDITCTRL_H_
#define FPDFSDK_PDFWINDOW_PWL_EDITCTRL_H_

#include <memory>

#include "core/fxcrt/fx_string.h"
#include "fpdfsdk/fxedit/fx_edit.h"
#include "fpdfsdk/pdfwindow/PWL_Wnd.h"

class CFX_Edit;
class CPWL_Caret;
class CPWL_Edit;
class CPWL_EditCtrl;
struct CPVT_SecProps;
struct CPVT_WordPlace;
struct CPVT_WordProps;
struct CPVT_WordRange;

enum PWL_EDIT_ALIGNFORMAT_H { PEAH_LEFT = 0, PEAH_MIDDLE, PEAH_RIGHT };

enum PWL_EDIT_ALIGNFORMAT_V { PEAV_TOP = 0, PEAV_CENTER, PEAV_BOTTOM };

class CPWL_EditCtrl : public CPWL_Wnd {
  friend class CPWL_Edit_Notify;

 public:
  CPWL_EditCtrl();
  ~CPWL_EditCtrl() override;

  CFX_WideString GetText() const;
  void SetSel(int32_t nStartChar, int32_t nEndChar);
  void GetSel(int32_t& nStartChar, int32_t& nEndChar) const;
  void Clear();
  void SelectAll();

  CFX_PointF GetScrollPos() const;
  void SetScrollPos(const CFX_PointF& point);

  void SetCharSet(uint8_t nCharSet) { m_nCharSet = nCharSet; }
  int32_t GetCharSet() const;

  bool CanUndo() const;
  bool CanRedo() const;
  void Redo();
  void Undo();

  void SetReadyToInput();

  // CPWL_Wnd
  void OnCreate(PWL_CREATEPARAM& cp) override;
  void OnCreated() override;
  bool OnKeyDown(uint16_t nChar, uint32_t nFlag) override;
  bool OnChar(uint16_t nChar, uint32_t nFlag) override;
  bool OnLButtonDown(const CFX_PointF& point, uint32_t nFlag) override;
  bool OnLButtonUp(const CFX_PointF& point, uint32_t nFlag) override;
  bool OnMouseMove(const CFX_PointF& point, uint32_t nFlag) override;
  void OnNotify(CPWL_Wnd* pWnd,
                uint32_t msg,
                intptr_t wParam = 0,
                intptr_t lParam = 0) override;
  void CreateChildWnd(const PWL_CREATEPARAM& cp) override;
  void RePosChildWnd() override;
  void SetFontSize(float fFontSize) override;
  float GetFontSize() const override;
  void SetCursor() override;

  void IOnSetScrollInfoY(float fPlateMin,
                         float fPlateMax,
                         float fContentMin,
                         float fContentMax,
                         float fSmallStep,
                         float fBigStep);
  void IOnSetScrollPosY(float fy);
  void IOnSetCaret(bool bVisible,
                   const CFX_PointF& ptHead,
                   const CFX_PointF& ptFoot,
                   const CPVT_WordPlace& place);
  void IOnInvalidateRect(CFX_FloatRect* pRect);

 protected:
  void CopyText();
  void PasteText();
  void CutText();
  void ShowVScrollBar(bool bShow);
  void InsertWord(uint16_t word, int32_t nCharset);
  void InsertReturn();

  bool IsWndHorV();

  void Delete();
  void Backspace();

  void GetCaretInfo(CFX_PointF* ptHead, CFX_PointF* ptFoot) const;
  void SetCaret(bool bVisible,
                const CFX_PointF& ptHead,
                const CFX_PointF& ptFoot);

  void SetEditCaret(bool bVisible);

  std::unique_ptr<CFX_Edit> m_pEdit;
  CPWL_Caret* m_pEditCaret;
  bool m_bMouseDown;

 private:
  void CreateEditCaret(const PWL_CREATEPARAM& cp);

  int32_t m_nCharSet;
};

#endif  // FPDFSDK_PDFWINDOW_PWL_EDITCTRL_H_
