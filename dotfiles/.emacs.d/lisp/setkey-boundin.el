;; setkey-boundin

;; Redefine key with existing functions ;;

(global-set-key "\C-x\C-m" 'execute-extended-command)
(global-set-key (kbd "C-h") 'delete-backward-char)
(global-set-key [home] 'beginning-of-buffer)
(global-set-key [end] 'end-of-buffer)

;; Define new functions ;;

;; comment
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

;; (setq bibtex-contline-indentation 20)
(setq bibtex-text-indentation 19)
(add-hook 'bibtex-mode-hook
          (lambda ()
            (define-key bibtex-mode-map "\C-x\C-a"
              'bibtex-reformat)))
;; 'bibtex-fill-entry `C-c C-q`

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
(global-set-key "\M-p" 'just-one-space-in-region)

;;
(provide 'setkey-boundin)
