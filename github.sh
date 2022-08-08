git init
git add .
git status -s
git commit -m "1.0"
git remote -v
git remote rm origin
git remote add origin git@github.com:YoooHaaa/PrivacyRom.git
git remote set-url origin git@github.com:YoooHaaa/PrivacyRom.git
git branch -M main
git push -u origin +main
