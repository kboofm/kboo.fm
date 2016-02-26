<h2 class="bg-primary">
  Latest Audio
</h2>


<?php foreach ($items as $item): ?>
  <p>
    Program Title
    <br />
    <a href="<?php print $item['url']; ?>">
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

