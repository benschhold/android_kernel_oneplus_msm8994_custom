rm -rf zipper/tools/Image.gz-dtb
rm -rf zipper/Bhenchod*
cp kernel/arch/arm64/boot/Image.gz-dtb zipper/tools/Image.gz-dtb
cd zipper
zip -r Haruhi-Kernel-v1-oneplus2-$(date +"%Y%m%d")-$(date +s).zip *
echo -e "Done"
