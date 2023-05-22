;; fontlock-boundin
;; https://github.com/emacs-mirror/emacs/blob/master/lisp/font-lock.el

;; Turn on Font lock mode
(global-font-lock-mode t)

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

;; function call https://www.reddit.com/r/emacs/comments/27eqwm/highlighting_c_member_function_calls/
(font-lock-add-keywords 'c++-mode
                        `((,(concat
                             "\\<[_a-zA-Z][_a-zA-Z0-9]*\\>"       ; Object identifier
                             "\\s *"                              ; Optional white space
                             "\\(?:\\.\\|->\\)"                   ; Member access
                             "\\s *"                              ; Optional white space
                             "\\<\\([_a-zA-Z][_a-zA-Z0-9]*\\)\\>" ; Member identifier
                             "\\s *"                              ; Optional white space
                             "(")                                 ; Paren for method invocation
                           1 'font-lock-warning-face))) ;; how=t will ignore comment and string escape
;; font-lock-function-call-face will be in 29.1

;;
(provide 'fontlock-boundin)
