THUMBDIR=thumbs
OPTIONS=-thumbnail "1024x1024>" -unsharp 0x.5 -quality 84

IMAGES=$(wildcard *.jpg)
THUMBS=$(foreach img, $(IMAGES), $(THUMBDIR)/$(img))

$(THUMBDIR)/%.jpg: %.jpg
	convert.exe $(@F) $(OPTIONS) $@

thumbs: $(THUMBS)
