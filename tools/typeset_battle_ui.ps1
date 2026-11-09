# Asset-authoring step only. Normal builds consume the checked-in PNG masks.
# Rasterize the seven fixed characters once on a 16x16 integer pixel grid.
Add-Type -AssemblyName System.Drawing
$assetRoot = Join-Path $PSScriptRoot '../assets/color/battle-ui/glyphs'
[IO.Directory]::CreateDirectory($assetRoot) | Out-Null
$uiFont = [Drawing.Font]::new('SimSun',16,[Drawing.FontStyle]::Regular,[Drawing.GraphicsUnit]::Pixel)
if ($uiFont.FontFamily.GetName(1033) -ne 'SimSun') { throw 'Install the matching SimSun font before authoring masks' }
$format = [Drawing.StringFormat]::GenericTypographic.Clone()
$format.FormatFlags = $format.FormatFlags -bor [Drawing.StringFormatFlags]::NoClip
$glyphImages = @{}
$cropLeft=32; $cropTop=32; $cropRight=0; $cropBottom=0
foreach ($glyph in '粮天信息查找?'.ToCharArray()) {
    $bitmap=[Drawing.Bitmap]::new(32,32,[Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $graphics=[Drawing.Graphics]::FromImage($bitmap)
    $graphics.Clear([Drawing.Color]::Transparent)
    $graphics.TextRenderingHint=[Drawing.Text.TextRenderingHint]::SingleBitPerPixelGridFit
    $glyphLeft = if ($glyph -eq '?') { 4 } else { 0 }
    $graphics.DrawString([string]$glyph,$uiFont,[Drawing.Brushes]::Black,[Drawing.PointF]::new($glyphLeft,0),$format)
    $graphics.Dispose()
    for ($y=0;$y -lt 32;$y++) { for ($x=0;$x -lt 32;$x++) {
        $alpha=$bitmap.GetPixel($x,$y).A
        if ($alpha -notin 0,255) { throw 'Text was antialiased' }
        if ($alpha -eq 255) {
            $cropLeft=[Math]::Min($cropLeft,$x);$cropTop=[Math]::Min($cropTop,$y)
            $cropRight=[Math]::Max($cropRight,$x+1);$cropBottom=[Math]::Max($cropBottom,$y+1)
        }
    }}
    $glyphImages[[string]$glyph]=$bitmap
}
if ($cropRight-$cropLeft -gt 16 -or $cropBottom-$cropTop -gt 16) { throw 'Glyph exceeds 16x16 cell' }
foreach ($glyph in $glyphImages.Keys) {
    $bitmap=$glyphImages[$glyph]
    $mask=$bitmap.Clone([Drawing.Rectangle]::new($cropLeft,$cropTop,16,16),[Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $glyphFile = if ($glyph -eq '?') { 'question_16x16.png' } else { $glyph+'_16x16.png' }
    $mask.Save((Join-Path $assetRoot $glyphFile),[Drawing.Imaging.ImageFormat]::Png)
    $mask.Dispose();$bitmap.Dispose()
}
$format.Dispose();$uiFont.Dispose()
[ordered]@{font='SimSun';font_file='simsun.ttc';font_file_sha256=(Get-FileHash -LiteralPath (Join-Path $env:WINDIR 'Fonts/simsun.ttc') -Algorithm SHA256).Hash.ToLowerInvariant();size_pixels=16;cell=@(16,16);common_crop_origin=@($cropLeft,$cropTop);rasterizer='System.Drawing SingleBitPerPixelGridFit';antialiasing=$false;runtime_font_dependency=$false;characters='粮天信息查找?'} | ConvertTo-Json | Set-Content -Encoding utf8 (Join-Path $assetRoot 'provenance.json')
Write-Output 'Baked seven 16x16 masks. No resizing or runtime font lookup.'
