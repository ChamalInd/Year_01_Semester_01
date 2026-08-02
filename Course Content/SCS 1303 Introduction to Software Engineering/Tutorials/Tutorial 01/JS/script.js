function Calculate() {
	r1 = Number(document.getElementById("r1").value);
	r2 = Number(document.getElementById("r2").value);

	if (r2 < r1 || r1 <= 0 || r2 <= 0) {
		alert("Invalid input");
	} else {
		let n = r2 - r1;
		let cost = fixed = tax = bill = 0;

		if (n < 30) {
			cost = n * 10;
			fixed = 75;
		} else if (n < 60) {
			cost = (30 * 10) + ((n - 30) * 30);
			fixed = 200;
		} else if (n < 90) {
			cost = (30 * 10) + (30 * 30) + ((n - 60) * 50);
			fixed = 400;
		} else if (n < 120) {
			cost = (30 * 10) + (30 * 30) + (30 * 50) + ((n - 90) * 70);
			fixed = 1000;
		} else if (n < 180) {
			cost = (30 * 10) + (30 * 30) + (30 * 50) + (30 * 70) + ((n - 120) * 110);
			fixed = 1500;
		} else {
			cost = (30 * 10) + (30 * 30) + (30 * 50) + (30 * 70) + (60 * 110) + ((n - 180) * 130);
			fixed = 2000;
		}
		
		tax = (cost + fixed) * 18 / 100;
		bill = cost + fixed + tax;
		
		document.getElementById("units").innerText = n;
		document.getElementById("charge").innerText = `Rs. ${cost.toLocaleString("en-US")}`;
		document.getElementById("fixed").innerText = `Rs. ${fixed.toLocaleString("en-US")}`;
		document.getElementById("vat").innerText = `Rs. ${tax.toLocaleString("en-US")}`;
		document.getElementById("bill").innerText = `Rs. ${bill.toLocaleString("en-US")}`;		

	}
}

