<?php

if (isset($_POST['submit'])) {
  $name = $_POST['name'];
  $mailFrom = $_POST['email'];
  $phone = $_POST['phoneNumber'];
  $message = $_POST['message'];

  $mailTo = "adrian.george.fagarasanu@gmail.com";
  $headers = "From: ".$mailFrom;
  $txt = "You have received an e-mail from ".$name.".\n
  With the phone number: ".$phone."\n\n".$message;

  mail($mailTo, "Website Message", $txt, $headers);
  header("Location: index.php?mailsend");
}

?>
