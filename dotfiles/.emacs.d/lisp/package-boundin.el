;; package-boundin
(require 'package)
(add-to-list 'package-archives
             '("melpa-stable" . "https://stable.melpa.org/packages/") t)
(package-initialize)

(setq package-selected-packages '(auto-complete company which-key web-mode helm)) 
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
  "Hooks for Web mode."
  (setq company-minimum-prefix-length 1
        company-idle-delay 0
        company-require-match nil
        company-tooltip-idle-delay 1
        company-tooltip-minimum 4
        company-tooltip-flip-when-above t
        company-format-margin-function #'company-vscode-dark-icons-margin) ;; yet work
  )
(add-hook 'company-mode-hook 'my-company-mode-hook)

;; which-key https://github.com/justbur/emacs-which-key ;; (require 'which-key)
(which-key-mode)
(set-face-attribute 'which-key-local-map-description-face nil :weight 'bold)
(which-key-setup-side-window-right-bottom)

;; helm-mode https://emacs-helm.github.io/helm/ ;; (require 'helm)
(helm-mode)
(define-key global-map [remap find-file] #'helm-find-files)
(define-key global-map [remap execute-extended-command] #'helm-M-x)
(define-key global-map [remap switch-to-buffer] #'helm-mini)
(custom-set-faces
 '(helm-selection ((t (:extend t :background "gray30" :distant-foreground "black"))))
 '(helm-match ((t (:inherit completions-common-part))))
 '(helm-source-header ((t (:inherit mode-line)))))

;; web-mode https://web-mode.org/
(web-mode)
(add-to-list 'auto-mode-alist '("\\.html?\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.js[x]?\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.css\\'" . web-mode))
(defun my-web-mode-hook ()
  "Hooks for Web mode."
  (setq web-mode-markup-indent-offset 2
        web-mode-css-indent-offset 4
        web-mode-code-indent-offset 2)
  (setq web-mode-enable-current-element-highlight t
        web-mode-enable-current-column-highlight t)
  (setq web-mode-enable-css-colorization t)
  (set-face-attribute 'web-mode-html-tag-bracket-face nil :foreground "gray30")
  )
(add-hook 'web-mode-hook  'my-web-mode-hook)

;;
(provide 'package-boundin)
