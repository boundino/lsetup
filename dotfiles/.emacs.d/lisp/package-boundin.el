;; package-boundin
(require 'package)
(add-to-list 'package-archives
             '("melpa" . "https://melpa.org/packages/") t)
(package-initialize)

(setq package-selected-packages '(auto-complete company which-key web-mode helm company-c-headers markdown-mode paren-face))
                                                ;; lsp-mode dap-mode yasnippet))
;; projectile hydra flycheck company avy which-key helm-xref dap-mode))

(when (cl-find-if-not #'package-installed-p package-selected-packages)
  (package-refresh-contents)
  (mapc #'package-install package-selected-packages))

;;

;; auto-complete https://github.com/auto-complete/auto-complete ;; (require 'auto-complete)
;; (ac-config-default)
;; company-mode https://company-mode.github.io/manual/Getting-Started.html ;; (require 'company-mode)
(global-company-mode)
(defun my-company-mode-hook ()
  "Hooks for Company mode."
  (setq company-minimum-prefix-length 1
        company-idle-delay 0.0
        company-require-match nil
        company-tooltip-idle-delay 1
        company-tooltip-minimum 4
        company-tooltip-flip-when-above t
        company-tooltip-align-annotations t
        company-format-margin-function #'company-text-icons-margin)
  (set-face-attribute 'company-tooltip-common nil :weight 'bold))
;; dark
(custom-set-faces
 '(company-tooltip ((t (:inherit default :background "gray25"))))
 '(company-tooltip-selection ((t (:background "gray20"))))
 '(company-scrollbar-bg ((t (:background "gray35"))))
 '(company-scrollbar-fg ((t (:background "gray50"))))
 '(company-tooltip-common ((t (:inherit completions-common-part))))
 '(company-tooltip-annotation ((t (:foreground "lightskyblue2"))))
 '(company-preview ((t (:inherit company-tooltip))))
 '(company-preview-common ((t (:inherit completions-common-part))))
 '(company-template-field ((t (:inherit company-tooltip :foreground "wheat1")))))
(add-hook 'company-mode-hook 'my-company-mode-hook)
;; company-c-headers
(add-to-list 'company-backends 'company-c-headers)
(custom-set-variables
 '(company-c-headers-path-user '("~" "../includes"))
 '(company-clang-arguments
   '("-I\"../includes\"" "-I\"../include\""
     "-I/Users/boundin" "-I/Users/boundin/buildroot/include" ;; local
     "-I/afs/cern.ch/user/w/wangj" "-I/usr/include/root"))) ;; lxplus

;; which-key https://github.com/justbur/emacs-which-key ;; (require 'which-key)
(which-key-mode)
(set-face-attribute 'which-key-local-map-description-face nil :weight 'bold)
;; (which-key-setup-side-window-right-bottom)

;; helm-mode https://emacs-helm.github.io/helm/ ;; (require 'helm)
(helm-mode)
(define-key global-map [remap find-file] #'helm-find-files)
(define-key global-map [remap execute-extended-command] #'helm-M-x)
(define-key global-map [remap switch-to-buffer] #'helm-mini)
(set-face-attribute 'helm-selection nil :background "gray25")
(set-face-attribute 'helm-ff-directory nil :background 'unspecified :foreground "darkseagreen3")
(set-face-attribute 'helm-ff-symlink nil :inherit 'font-lock-keyword-face)
(set-face-attribute 'helm-ff-file-extension nil :foreground "indianred1")
(set-face-attribute 'helm-ff-dotted-directory nil :background 'unspecified :foreground "white" :weight 'bold)
(set-face-attribute 'helm-ff-file nil :inherit 'font-lock-variable-name-face)
(set-face-attribute 'helm-ff-executable nil :foreground "gold1")
(set-face-attribute 'helm-candidate-number nil :background "wheat1" :foreground "black")
(custom-set-faces
 '(helm-match ((t (:inherit completions-common-part))))
 '(helm-source-header ((t (:inherit mode-line)))))

;; web-mode https://web-mode.org/
(web-mode)
(add-to-list 'auto-mode-alist '("\\.html?\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.js[xon]?\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.css\\'" . web-mode))
(defun my-web-mode-hook ()
  "Hooks for Web mode."
  (setq web-mode-markup-indent-offset 2
        web-mode-css-indent-offset 4
        web-mode-code-indent-offset 4)
  (setq web-mode-enable-current-element-highlight t
        web-mode-enable-current-column-highlight t)
  (setq web-mode-enable-css-colorization t)
  (set-face-attribute 'web-mode-html-tag-bracket-face nil :foreground "gray30")
  (set-face-attribute 'web-mode-function-call-face nil :inherit 'font-lock-warning-face))
(add-hook 'web-mode-hook  'my-web-mode-hook)

;; markdown-mode
(custom-set-faces
 '(markdown-url-face ((t (:inherit font-lock-variable-name-face))))
 '(markdown-header-face ((t (:inherit font-lock-function-name-face)))))

;; paren-face https://github.com/tarsius/paren-face
(global-paren-face-mode)
(setq paren-face-modes '(lisp-mode emacs-lisp-mode lisp-interaction-mode ielm-mode
                                   scheme-mode inferior-scheme-mode clojure-mode
                                   cider-repl-mode nrepl-mode arc-mode inferior-arc-mode
                                   c++-mode sh-mode))

;; lsp-mode c++ https://emacs-lsp.github.io/lsp-mode/tutorials/CPP-guide/
;; https://emacs-lsp.github.io/lsp-mode/tutorials/how-to-turn-off/
;; (add-hook 'c-mode-hook 'lsp)
;; (add-hook 'c++-mode-hook 'lsp)
;; (setq gc-cons-threshold (* 100 1024 1024)
;;       read-process-output-max (* 1024 1024)
;;       treemacs-space-between-root-nodes nil
;;       lsp-idle-delay 0.1  ;; clangd is fast
;;       lsp-diagnostics-provider :none
;;       ;; lsp-completion-show-kind nil
;;       lsp-completion-provider :none)
;; (setq lsp-clients-clangd-args '("--header-insertion-decorators=0" "--compile-commands-dir=build"))
;; (with-eval-after-load 'lsp-mode
;;   (add-hook 'lsp-mode-hook #'lsp-enable-which-key-integration)
;;   (require 'dap-cpptools)
;;   (yas-global-mode))

;;
(provide 'package-boundin)
