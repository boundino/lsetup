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
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(company-c-headers-path-user '("~" "../includes"))
 '(company-clang-arguments
   '("-I\"../includes\"" "-I\"../include\"" "-I/Users/boundin" "-I/Users/boundin/buildroot/include" "-I/afs/cern.ch/user/w/wangj" "-I/usr/include/root"))
 '(package-selected-packages '(which-key)))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(company-preview ((t (:inherit company-tooltip))))
 '(company-preview-common ((t (:inherit completions-common-part))))
 '(company-template-field ((t (:inherit company-tooltip :foreground "wheat1"))))
 '(company-tooltip ((t (:inherit default :background "gray25"))))
 '(company-tooltip-annotation ((t (:foreground "lightskyblue2"))))
 '(company-tooltip-common ((t (:inherit completions-common-part))))
 '(company-tooltip-scrollbar-thumb ((t (:background "gray50"))))
 '(company-tooltip-scrollbar-track ((t (:background "gray35"))))
 '(company-tooltip-selection ((t (:background "gray20"))))
 '(helm-match ((t (:inherit completions-common-part))))
 '(helm-source-header ((t (:inherit mode-line))))
 '(markdown-header-face ((t (:inherit font-lock-function-name-face))))
 '(markdown-url-face ((t (:inherit font-lock-variable-name-face)))))
