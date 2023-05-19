;; package-boundin
(require 'package)
(add-to-list 'package-archives
             '("melpa" . "https://melpa.org/packages/") t)
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

;; which-key https://github.com/justbur/emacs-which-key ;; (require 'which-key)
(which-key-mode)
(set-face-attribute 'which-key-local-map-description-face nil :weight 'bold)
;; (which-key-setup-side-window-right-bottom)

;; helm-mode https://emacs-helm.github.io/helm/ ;; (require 'helm)
(helm-mode)
(define-key global-map [remap find-file] #'helm-find-files)
(define-key global-map [remap execute-extended-command] #'helm-M-x)
(define-key global-map [remap switch-to-buffer] #'helm-mini)
(custom-set-faces
 '(helm-selection ((t (:extend t :background "gray20" :distant-foreground "black"))))
 '(helm-match ((t (:inherit completions-common-part))))
 '(helm-source-header ((t (:inherit mode-line))))
 '(helm-ff-directory ((t (:extend t :foreground "darkseagreen3"))))
 '(helm-ff-symlink ((t (:extend t :foreground "steelblue3"))))
 '(helm-ff-file-extension ((t (:foreground "indianred1" :extend t))))
 '(helm-ff-dotted-directory ((t (:extend t :foreground "darkolivegreen2"))))
 '(helm-ff-file ((t (:extend t :foreground "wheat2"))))
 '(helm-ff-executable ((t (:extend t :foreground "gold1"))))
 '(helm-candidate-number ((t (:background "wheat1" :foreground "black")))))

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
  (set-face-attribute 'web-mode-html-tag-bracket-face nil :foreground "gray30"))
(add-hook 'web-mode-hook  'my-web-mode-hook)

;;
(provide 'package-boundin)
