<div class="row margin-vertical-lg">
  <div class="col-md-8 col-md-offset-2">
    <div id="flickr-gallery"
         class="carousel slide"
         data-interval="false"
         data-ride="carousel">


      <ol class="carousel-indicators">
        <?php foreach ($flickr_gallery as $index => $flickr_item): ?>
          <li data-target="#flickr-gallery"
              data-slide-to="<?php print $index; ?>"
              class="<?php if ($index == 0): ?>active<?php endif; ?>">
          </li>
        <?php endforeach; ?>
      </ol>


      <div class="carousel-inner" role="listbox">
        <?php foreach ($flickr_gallery as $index => $flickr_item): ?>
          <div class="item <?php if ($index == 0): ?>active<?php endif; ?>">
            <a href="<?php print $flickr_item['url']; ?>"
               target="_blank">

              <img height="300"
                   width="500"
                   src="<?php print $flickr_item['image']; ?>"
                   alt="<?php print $flickr_item['alt']; ?>">
            </a>


            <div class="carousel-caption">
              <?php print $flickr_item['caption']; ?>
            </div>
          </div>
        <?php endforeach; ?>
      </div>


      <a class="left carousel-control"
         href="#flickr-gallery"
         role="button"
         data-slide="prev">

        <span class="fa fa-arrow-left" aria-hidden="true"></span>
        <span class="sr-only">Previous</span>
      </a>


      <a class="right carousel-control"
         href="#flickr-gallery"
         role="button"
         data-slide="next">

        <span class="fa fa-arrow-right" aria-hidden="true"></span>
        <span class="sr-only">Next</span>
      </a>
    </div>
  </div>
</div>
