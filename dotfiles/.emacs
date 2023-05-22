;; .emacs

(add-to-list 'load-path "~/.emacs.d/lisp/")

;; Set dark theme ;; 
(setq frame-background-mode 'dark)
(mapc 'frame-set-background-mode (frame-list))

;; Color theme ;;
(require 'color-theme-boundin)
(setq color-theme-is-global t)
(color-theme-initialize)
(color-theme-boundin)

;; Load setup ;;
(require 'package-boundin)
(require 'fontlock-boundin)
(require 'setkey-boundin)

;; Set variables ;;
;; Highlight parenthese
(show-paren-mode t)
;; Add space in linum mode
(setq linum-format "%d ")
;; display column number
(column-number-mode t)
;; default to better frame titles
(setq frame-title-format
      (concat  "%b - emacs@" (system-name)))
;; default to unified diffs
(setq diff-switches "-u")
(put 'upcase-region 'disabled nil)
;; turn on transient-mark
(transient-mark-mode t)
(setq x-select-enable-clipboard t)
;; Allow open symlinks
(setq vc-follow-symlinks nil)
;; (setq org-confirm-babel-evaluate nil)

;; ;; uncomment this line to disable loading of "default.el" at startup
;;(setq inhibit-default-init t)
;; ;; always end a file with a newline
;; (setq require-final-newline 'query)
;; ;; enable visual feedback on selections
;; (setq transient-mark-mode t)
;; (setq vc-handled-backends ())

;; Auto mode ;;
(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))
(add-to-list 'auto-mode-alist '("\\.c\\'" . c++-mode))
(add-to-list 'auto-mode-alist '("\\.bash.*\\'" . sh-mode))
(add-to-list 'auto-mode-alist '("\\.shinc\\'" . sh-mode))

;; Add hook ;;
;; Indent
(setq-default indent-tabs-mode nil)
(add-hook 'bibtex-mode-hook
          (lambda () (setq fill-column 999999)))
