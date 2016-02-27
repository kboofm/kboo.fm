<h2 class="bg-info">
  Recent Playlists
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
  <a class="more-link bg-info"
     href="#">
    More
  </a>
</p>
