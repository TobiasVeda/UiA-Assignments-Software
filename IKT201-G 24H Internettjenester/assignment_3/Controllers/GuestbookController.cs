using assignment_3.Models;
using assignment_3.Data;
using Microsoft.AspNetCore.Mvc;

namespace assignment_3.Controllers;

public class GuestbookController : Controller{

    // For local use. Wil be interface for global db
    private readonly ApplicationDbContext _db;
    
    
    public GuestbookController(ApplicationDbContext db){
        // Retrieved reference to global db
        _db = db;
    }

    [HttpGet]
    public IActionResult Index(){
        var guests = _db.Guests.ToList();
        return View(guests);
    }
    
    [HttpGet]
    public IActionResult Add(){
        return View();
    }
    
    [HttpPost]
    public IActionResult Add(Guest guest){
        
        if (!ModelState.IsValid)
            return View(guest);
        
        _db.Guests.Add(guest);
        _db.SaveChanges();
        
        return RedirectToAction(nameof(Index));
    }
}