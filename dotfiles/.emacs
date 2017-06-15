;; .emacs

;; Color themee
(add-to-list 'load-path "~/.emacs.d/lisp/")
(require 'color-theme)
(color-theme-initialize)
(color-theme-clarity)

;; Highlight parenthese
(show-paren-mode t)

;; Turn on Font lock mode
(global-font-lock-mode t)

;; Set key globally
(global-set-key "\C-x\C-m" 'execute-extended-command)
(global-set-key (kbd "C-h") 'delete-backward-char)
(global-set-key [home] 'beginning-of-buffer)
(global-set-key [end] 'end-of-buffer)

;; uncomment this line to disable loading of "default.el" at startup
;(setq inhibit-default-init t)

;; turn on font-lock mode
(when (fboundp 'global-font-lock-mode)
  (global-font-lock-mode t))

;; enable visual feedback on selections
;(setq transient-mark-mode t)

;; default to better frame titles
(setq frame-title-format
      (concat  "%b - emacs@" (system-name)))

;; default to unified diffs
(setq diff-switches "-u")

;; always end a file with a newline
;(setq require-final-newline 'query)

(put 'upcase-region 'disabled nil)

;; turn on transient-mark
(transient-mark-mode t)

(setq x-select-enable-clipboard t)

;; display column number
(column-number-mode t)

;; indent
(setq-default indent-tabs-mode nil)

;; 
(setq tags-table-list '"~/.emacs.d/git/tags-view/tags-view.el")