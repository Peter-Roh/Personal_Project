const modal = document.getElementById("modal__window");
const modal_btn = document.getElementById("modal");
const plus = document.getElementById("plus");

function handleModal() {
    modal.style.display = 'none';
}

function handlePlus() {
    modal.style.removeProperty("display");
    modal.style.display("flex");
}

modal_btn.addEventListener("click", handleModal);
plus.addEventListener("click", handlePlus);
