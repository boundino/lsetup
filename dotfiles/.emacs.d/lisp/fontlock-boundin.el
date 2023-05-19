;; fontlock-boundin

;; latex-mode
(font-lock-add-keywords 'latex-mode
                        '(("rmdme{\\([^}]+\\)}"
                           1
                           'font-lock-comment-face)))
(font-lock-add-keywords 'latex-mode
                        '(("ref{\\([^}]+\\)}"
                           1
                           'font-lock-variable-name-face)))
(font-lock-add-keywords 'latex-mode
                        '(("label{\\([^}]+\\)}"
                           1
                           'font-lock-variable-name-face)))


;;
(provide 'fontlock-boundin)
