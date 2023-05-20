(eval-when-compile
  (require 'color-theme))

(defun color-theme-boundin ()
  "based on clarity: White on black color theme by Richard Wellum, created 2003-01-16."
  (interactive)
  (color-theme-install
   '(color-theme-boundin
     ;; ((background-color . "black")
     ((background-mode . dark)
      (border-color . "white")
      (cursor-color . "yellow")
      (foreground-color . "#ffffff")
      (mouse-color . "yellow"))
     ((CUA-mode-global-mark-cursor-color . "cyan")
      (CUA-mode-normal-cursor-color . "yellow")
      (CUA-mode-overwrite-cursor-color . "red")
      (CUA-mode-read-only-cursor-color . "green")
      (help-highlight-face . underline)
      (ibuffer-dired-buffer-face . font-lock-function-name-face)
      (ibuffer-help-buffer-face . font-lock-comment-face)
      (ibuffer-hidden-buffer-face . font-lock-warning-face)
      (ibuffer-occur-match-face . font-lock-warning-face)
      (ibuffer-read-only-buffer-face . font-lock-type-face)
      (ibuffer-special-buffer-face . font-lock-keyword-face)
      (ibuffer-title-face . font-lock-type-face)
      (list-matching-lines-face . bold)
      (ps-line-number-color . "black")
      (ps-zebra-color . 0.95)
      (tags-tag-face . default)
      (view-highlight-face . highlight)
      (widget-mouse-face . highlight))
     (default ((t (nil))))
     (CUA-global-mark-face ((t (:background "cyan" :foreground "black"))))
     (CUA-rectangle-face ((t (:background "maroon" :foreground "white"))))
     (CUA-rectangle-noselect-face ((t (:background "dimgray" :foreground "white"))))
     (bold ((t (:bold t :weight bold))))
     (bold-italic ((t (:italic t :bold t :slant italic :weight bold))))
     (border ((t (:background "white"))))
     (clearcase-dired-checkedout-face ((t (:foreground "red"))))
     (comint-highlight-input ((t (:bold t :weight bold))))
     (comint-highlight-prompt ((t (:foreground "cyan"))))
     (cursor ((t (:background "yellow"))))
     (custom-variable-tag ((t (:foreground "darkseagreen" :weight bold))))
     (fixed-pitch ((t (:family "courier"))))
     (flash-paren-face-off ((t (nil))))
     (flash-paren-face-on ((t (nil))))
     (flash-paren-face-region ((t (nil))))
     (font-lock-builtin-face ((t (:foreground "pink1"))))
     (font-lock-comment-face ((t (:foreground "indianred" :weight light))))
     (font-lock-constant-face ((t (:foreground "cadetblue1"))))
     (font-lock-doc-face ((t (:foreground "darkolivegreen2"))))
     (font-lock-function-name-face ((t (:foreground "lightsalmon1"))))
     (font-lock-keyword-face ((t (:foreground "cadetblue"))))
     (font-lock-string-face ((t (:foreground "lightskyblue1" :weight semilight))))
     (font-lock-type-face ((t (:foreground "darkolivegreen2"))))
     (font-lock-variable-name-face ((t (:foreground "burlywood1"))))
     (font-lock-warning-face ((t (:bold t :foreground "Pink" :weight bold))))
     (fringe ((t (:background "grey10"))))
     (header-line ((t (:box (:line-width -1 :style released-button) :foreground "grey20" :background "grey90" :box nil))))
     (highlight ((t (:background "darkolivegreen"))))
     (ibuffer-deletion-face ((t (:foreground "red"))))
     (ibuffer-marked-face ((t (:foreground "green"))))
     (isearch ((t (:background "lightgoldenrod1" :foreground "aquamarine4" :weight bold))))
     (isearch-fail ((t (:background "firebrick"))))
     (isearch-lazy-highlight-face ((t (:background "paleturquoise4"))))
     (italic ((t (:italic t :slant italic))))
     (lazy-highlight ((t (:background "paleturquoise4"))))
     (menu ((t (nil))))
     (mode-line ((t (:background "deepskyblue4" :foreground "antiquewhite" :box nil))))
     (mouse ((t (:background "white"))))
     (region ((t (:background "palegreen4"))))
     (scroll-bar ((t (nil))))
     (secondary-selection ((t (:background "darkslateblue"))))
     (show-block-face1 ((t (:background "gray10"))))
     (show-block-face2 ((t (:background "gray15"))))
     (show-block-face3 ((t (:background "gray20"))))
     (show-block-face4 ((t (:background "gray25"))))
     (show-block-face5 ((t (:background "gray30"))))
     (show-block-face6 ((t (:background "gray35"))))
     (show-block-face7 ((t (:background "gray40"))))
     (show-block-face8 ((t (:background "gray45"))))
     (show-block-face9 ((t (:background "gray50"))))
     (show-paren-match ((t (:background "paleturquoise" :foreground "black"))))
     (show-paren-match-face ((t (:background "paleturquoise" :foreground "black"))))
     (show-paren-mismatch-face ((t (:background "purple" :foreground "white"))))
     (tool-bar ((t (:background "grey75" :foreground "black" :box (:line-width 1 :style released-button)))))
     (tooltip ((t (:background "lightyellow" :foreground "black"))))
     (trailing-whitespace ((t (:background "red"))))
     (underline ((t (:underline t))))
     (variable-pitch ((t (:family "helv"))))
     (widget-button-face ((t (:bold t :weight bold))))
     (widget-button-pressed-face ((t (:foreground "red"))))
     (widget-documentation-face ((t (:foreground "lime green"))))
     (widget-field ((t (:extend t :background "darkslategray" :foreground "whitesmoke"))))
     (widget-field-face ((t (:background "dim gray"))))
     (widget-inactive-face ((t (:foreground "light gray"))))
     (widget-single-line-field-face ((t (:background "dim gray"))))
     (minibuffer-prompt ((t (:foreground "gold"))))
     (completions-common-part ((t (:foreground "darkolivegreen2"))))
     (link ((t (:foreground "lightskyblue" :underline t))))
     )))

(provide 'color-theme-boundin)
