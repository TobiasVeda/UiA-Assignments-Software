using Microsoft.AspNetCore.Mvc;

namespace assignment_2.Controllers;

public class CalculatorController : Controller{
    // GET
    public IActionResult Index(){
        return View();
    }
}