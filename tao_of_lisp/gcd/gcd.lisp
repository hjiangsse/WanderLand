(defun euclid-gcd (m n)
  (let* ((n-m (max m n))
         (n-n (min m n))
         (remainer (mod n-m n-n)))
    (if (equal remainer 0)
        n-n
      (euclid-gcd n-n remainer))))
