<h2 class="bg-primary">
  Latest Audio
</h2>


<?php foreach ($items as $item): ?>
  <p>
    <span class="truncate">
      <?php print $item['program']; ?>
    </span>
    <br />

    <a href="<?php print $item['url']; ?>"
       class="truncate">
      <?php print $item['title']; ?>
    </a>
  </p>
<?php endforeach; ?>


<p>
  <a class="more-link bg-primary"
     href="#">
    More
  </a>
</p>

