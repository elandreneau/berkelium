/*  Berkelium - Embedded Chromium
 *  WindowDelegate.hpp
 *
 *  Copyright (c) 2009, Patrick Reiter Horn
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of Sirikata nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _BERKELIUM_WINDOW_DELEGATE_HPP_
#define _BERKELIUM_WINDOW_DELEGATE_HPP_

#include <vector>

namespace Berkelium {

class WindowImpl;
class Widget;
class Window;

class RenderWidget; // FIXME: private interface.

class Cursor;

struct ContextMenuEventArgs {
  enum MediaType {
      MediaTypeNone,
      MediaTypeImage,
      MediaTypeVideo,
      MediaTypeAudio,
  };
  enum EditFlags {
      CanDoNone = 0x0,
      CanUndo = 0x1,
      CanRedo = 0x2,
      CanCut = 0x4,
      CanCopy = 0x8,
      CanPaste = 0x10,
      CanDelete = 0x20,
      CanSelectAll = 0x40,
  };

  MediaType mediaType;

  int mouseX, mouseY;

  const wchar_t * linkUrl, * srcUrl, * pageUrl, * frameUrl, * selectedText;
  size_t linkUrlLength, srcUrlLength, pageUrlLength, frameUrlLength, selectedTextLength;

  bool isEditable;

  int editFlags;
};

class BERKELIUM_EXPORT WindowDelegate {
public:
    virtual ~WindowDelegate() {}

    virtual void onAddressBarChanged(Window *win, const char* newURL, size_t newURLSize) {}
    virtual void onStartLoading(Window *win, const char *newURL, size_t newURLSize) {}
    virtual void onLoad(Window *win) {}
    virtual void onLoadError(Window *win, const char* error, size_t errorLength) {}
    virtual void onProvisionalLoadError(Window *win, const char * url, size_t urlLength, int errorCode, bool isMainFrame) {}
    virtual void onNavigationRequested(Window *win, const wchar_t *newUrl, size_t newUrlLength, const wchar_t *referrer, size_t referrerLength, bool isNewWindow, bool &cancelDefaultAction) {}
    virtual void onLoadingStateChanged(Window *win, bool isLoading) {}
    virtual void onTitleChanged(Window *win, const wchar_t *title, size_t titleLength) {}
    virtual void onTooltipChanged(Window *win, const wchar_t *text, size_t textLength) {}

    virtual void onCrashed(Window *win) {}
    virtual void onUnresponsive(Window *win) {}
    virtual void onResponsive(Window *win) {}
    struct Data {
        const char *message;
        size_t length;
    };
    virtual void onChromeSend(
        Window *win,
        Data message,
        const Data* content,
        size_t numContents) {}

    virtual void onCreatedWindow(Window *win, Window *newWindow, const Rect &initialRect) {}

    virtual void onPaint(
        Window *win,
        const unsigned char *sourceBuffer,
        const Rect &rect,
        int dx, int dy,
        const Rect &scrollRect) {}

    virtual void onWidgetCreated(Window *win, Widget *newWidget, int zIndex) {}
    virtual void onWidgetDestroyed(Window *win, Widget *newWidget) {}

    virtual void onWidgetResize(
        Window *win,
        Widget *wid,
        int newWidth,
        int newHeight) {}

    virtual void onWidgetMove(
        Window *win,
        Widget *wid,
        int newX,
        int newY) {}

    virtual void onWidgetPaint(
        Window *win,
        Widget *wid,
        const unsigned char *sourceBuffer,
        const Rect &rect,
        int dx, int dy,
        const Rect &scrollRect) {}

    /** Invoked when the Window requests that the mouse cursor be updated. */
    virtual void onCursorUpdated(const Cursor& newCursor) {}

    virtual void onShowContextMenu(Window *win, const ContextMenuEventArgs& args) {}

/**************************
   Might want messages for:
- ShowContextMenu(const ContextMenuParams& params);
- StartDragging(const WebDropData& drop_data,
                WebKit::WebDragOperationsMask allowed_ops);
- UpdateDragCursor(WebKit::WebDragOperation operation);
- TakeFocus(bool reverse)

- Renderer[Un]Responsive

- RequestOpenURL
- DocumentAvailableInMainFrame
- DidStartLoading
- DidStopLoading
- Close
- UpdateTargetURL
- UpdateTitle
- UpdateEncoding
- UpdateState????
- DidNavigate

   Also, may want API to bind javascript functions.
**************************/

};

}

#endif
