;; .emacs

;; Color themee
(add-to-list 'load-path "~/.emacs.d/lisp/")
(require 'color-theme-boundin)
;;(require 'fun-boundin)

(setq color-theme-is-global t)
(color-theme-initialize)
(color-theme-boundin)

;; Highlight parenthese
(show-paren-mode t)

;; Turn on Font lock mode
(global-font-lock-mode t)

;; Set key globally
(global-set-key "\C-x\C-m" 'execute-extended-command)
(global-set-key (kbd "C-h") 'delete-backward-char)
(global-set-key [home] 'beginning-of-buffer)
(global-set-key [end] 'end-of-buffer)

;; auto-mode
(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))
(add-to-list 'auto-mode-alist '("\\.md\\'" . html-mode))

;; uncomment this line to disable loading of "default.el" at startup
;;(setq inhibit-default-init t)

;; turn on font-lock mode
(when (fboundp 'global-font-lock-mode)
  (global-font-lock-mode t))

;; enable visual feedback on selections
;;(setq transient-mark-mode t)

;; default to better frame titles
(setq frame-title-format
      (concat  "%b - emacs@" (system-name)))

;; default to unified diffs
(setq diff-switches "-u")

;; always end a file with a newline
;;(setq require-final-newline 'query)

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

;;
(setq vc-follow-symlinks nil)
;; (setq org-confirm-babel-evaluate nil)

;;
(defun comment-or-uncomment-region-or-line ()
  "Comments or uncomments the region or the current line if there's no active region."
  (interactive)
  (let (beg end)
    (if (region-active-p)
        (setq beg (region-beginning) end (region-end))
      (setq beg (line-beginning-position) end (line-end-position)))
    (comment-or-uncomment-region beg end)))
(provide 'comment-or-uncomment-region-or-line)

(global-set-key "\M-;" 'comment-or-uncomment-region-or-line)

(defun indent-whole-buffer ()
  (interactive)
  (save-excursion
    (indent-region (point-min) (point-max) nil)))
(provide 'indent-whole-buffer)
(global-set-key "\C-x\C-a" 'indent-whole-buffer)


(defun just-one-space-in-region (beg end)
  "replace all whitespace in the region with single spaces"
  (interactive "r")
  (save-excursion
    (save-restriction
      (narrow-to-region beg end)
      (goto-char (point-min))
      (while (re-search-forward "\\s-+" nil t)
        (replace-match " ")))))
(provide 'just-one-space-in-region)